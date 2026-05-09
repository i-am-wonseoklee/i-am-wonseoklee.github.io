import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import place_poles
from scipy.linalg import solve_continuous_are
from scipy.integrate import solve_ivp
from matplotlib.animation import FuncAnimation
from matplotlib.patches import Circle, Rectangle

# Parameters.
m = 1.0
M = 5.0
L = 2.0
g = -9.81
delta = 1.0


def calculate_K_man(
    A: np.ndarray, B: np.ndarray, desired_poles: np.ndarray
) -> np.ndarray:
    """Calculate the K gain matrix using manual pole placement.

    Args:
        A (np.ndarray): The state matrix of the system.
        B (np.ndarray): The input matrix of the system.
        desired_poles (np.ndarray): The desired pole locations for the closed-loop system.

    Returns:
        np.ndarray: The gain matrix K that places the poles at the desired locations.
    """
    return place_poles(A, B, desired_poles).gain_matrix


def calculate_K_lqr(
    A: np.ndarray, B: np.ndarray, Q: np.ndarray, R: np.ndarray
) -> np.ndarray:
    """Calculate the K gain matrix using Linear Quadratic Regulator (LQR) method.

    Args:
        A (np.ndarray): The state matrix of the system.
        B (np.ndarray): The input matrix of the system.
        Q (np.ndarray): The state weighting matrix.
        R (np.ndarray): The input weighting matrix.

    Returns:
        np.ndarray: The gain matrix K that minimizes the LQR cost function.
    """
    # Solve the continuous-time algebraic Riccati equation.
    P = solve_continuous_are(A, B, Q, R)
    # Calculate the LQR gain matrix K.
    K = np.linalg.inv(R) @ B.T @ P
    return K


def simulate_system(
    A: np.ndarray, B: np.ndarray, K: np.ndarray, x0: np.ndarray, t: np.ndarray
) -> np.ndarray:
    """Simulate the closed-loop system response.

    Args:
        A (np.ndarray): The state matrix of the system.
        B (np.ndarray): The input matrix of the system.
        K (np.ndarray): The gain matrix for state feedback control.
        x0 (np.ndarray): The initial state of the system.
        t (np.ndarray): The time vector for simulation.

    Returns:
        np.ndarray: The state trajectory of the system over time.
    """

    def closed_loop_dynamics(_t, x):
        u = -K @ x
        dxdt = A @ x + B @ u
        return dxdt

    sol = solve_ivp(closed_loop_dynamics, [t[0], t[-1]], x0, t_eval=t)
    return sol.y


def generate_gif(
    A: np.ndarray,
    B: np.ndarray,
    K: np.ndarray,
    x0: np.ndarray,
    t: np.ndarray,
    filename: str,
) -> None:
    """Generate a GIF animation of the inverted pendulum on a cart system.

    Args:
        A (np.ndarray): The state matrix of the system.
        B (np.ndarray): The input matrix of the system.
        K (np.ndarray): The gain matrix for state feedback control.
        x0 (np.ndarray): The initial state of the system.
        t (np.ndarray): The time vector for simulation.
        filename (str): The name of the output GIF file.
    """

    # Simulate the system to get the state trajectory.
    states = simulate_system(A, B, K, x0, t)

    # Simple schematic dimensions (not to scale).
    cart_width = 1.4
    cart_height = 0.5
    wheel_radius = 0.16
    bob_radius = 0.17
    wheel_offset = 0.42
    ground_y = 0.0
    cart_bottom_y = ground_y + 2.0 * wheel_radius
    pivot_y = cart_bottom_y + cart_height

    x_margin = 2.0
    x_min = float(np.min(states[0]) - x_margin)
    x_max = float(np.max(states[0]) + x_margin)
    y_min = -0.15
    y_max = pivot_y + L + 0.8

    # Create a figure and axis for plotting.
    fig, ax = plt.subplots(figsize=(8, 4.8))
    ax.set_xlim(x_min, x_max)
    ax.set_ylim(y_min, y_max)
    ax.set_aspect("equal")
    ax.axis("off")

    # Ground line.
    ax.plot([x_min - 1.0, x_max + 1.0], [ground_y, ground_y], "k-", lw=3)

    # Cart body and wheels.
    cart = Rectangle(
        (-cart_width / 2.0, cart_bottom_y),
        cart_width,
        cart_height,
        facecolor="royalblue",
        edgecolor="black",
        linewidth=2,
    )
    left_wheel = Circle(
        (-wheel_offset, wheel_radius),
        wheel_radius,
        facecolor="black",
        edgecolor="black",
    )
    right_wheel = Circle(
        (wheel_offset, wheel_radius),
        wheel_radius,
        facecolor="black",
        edgecolor="black",
    )
    ax.add_patch(cart)
    ax.add_patch(left_wheel)
    ax.add_patch(right_wheel)

    # Pendulum and helper lines.
    (reference_line,) = ax.plot([], [], "k--", lw=2, dashes=(6, 4))
    (rod_line,) = ax.plot([], [], "k-", lw=3)
    bob = Circle(
        (0.0, 0.0), bob_radius, facecolor="red", edgecolor="black", linewidth=2
    )
    ax.add_patch(bob)

    def update(frame):
        x = float(states[0, frame])
        theta = float(states[2, frame])

        # Update cart and wheel positions.
        cart.set_xy((x - cart_width / 2.0, cart_bottom_y))
        left_wheel.center = (x - wheel_offset, wheel_radius)
        right_wheel.center = (x + wheel_offset, wheel_radius)

        # Pendulum is modeled around the upright position (theta=0).
        pivot_x = x
        bob_x = pivot_x + L * np.sin(theta)
        bob_y = pivot_y + L * np.cos(theta)

        reference_line.set_data([pivot_x, pivot_x], [pivot_y - 0.05, pivot_y + L + 0.2])
        rod_line.set_data([pivot_x, bob_x], [pivot_y, bob_y])
        bob.center = (bob_x, bob_y)

        return cart, left_wheel, right_wheel, reference_line, rod_line, bob

    # Create an animation and save it as a GIF.
    anim = FuncAnimation(fig, update, frames=len(t), blit=True)
    anim.save(filename, writer="pillow", fps=30)
    plt.close(fig)


# A matrix.
A = np.array(
    [
        [0, 1, 0, 0],
        [0, -delta / M, m * g / M, 0],
        [0, 0, 0, 1],
        [0, -delta / (M * L), -(m + M) * g / (M * L), 0],
    ]
)

# B matrix.
B = np.array([[0], [1 / M], [0], [1 / (M * L)]])

# Controllability matrix.
C = np.hstack((B, A @ B, A @ A @ B, A @ A @ A @ B))

# K using manual pole placement.
K_man = calculate_K_man(A, B, np.array([-1, -1.5, -2, -2.5]))

# K using LQR.
K_lqr = calculate_K_lqr(A, B, Q=np.diag([1, 1, 10, 1]), R=20 * np.eye(1))

generate_gif(
    A,
    B,
    K_man,
    x0=np.array([0.0, 0.0, np.pi / 6, 0.0]),
    t=np.linspace(0, 10, 300),
    filename="inverted_pendulum_cart_man.gif",
)

generate_gif(
    A,
    B,
    K_lqr,
    x0=np.array([0.0, 0.0, np.pi / 6, 0.0]),
    t=np.linspace(0, 10, 300),
    filename="inverted_pendulum_cart_lqr.gif",
)
