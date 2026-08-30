import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

EX = np.array([-0.58, -0.33]); EY = np.array([1.0, 0.0]); EZ = np.array([0.0, 1.0])
def P(v):
    v = np.asarray(v, float)
    return v[0]*EX + v[1]*EY + v[2]*EZ

r     = np.array([0.62, 0.95, 0.95])
r_par = np.array([0.0, 0.0, r[2]])
r_per = r - r_par
R     = np.linalg.norm(r_per)

C_R, C_PAR, C_PER, C_W, C_V = '#1f4e79', '#767676', '#c0504d', '#4f81bd', '#548235'

fig, ax = plt.subplots(figsize=(6.8, 5.0))

# rotation axis
ax.plot(*zip(P([0,0,-0.42]), P([0,0,1.15])), color='0.62', lw=1.0, zorder=1)
ax.annotate('', xy=P([0,0,1.95]), xytext=P([0,0,1.10]),
            arrowprops=dict(arrowstyle='-|>', color='0.62', lw=1.0,
                            shrinkA=0, shrinkB=0, mutation_scale=13), zorder=1)

# circle traced by the tip of r
t = np.linspace(0, 2*np.pi, 400)
circ = np.array([P([R*np.cos(a), R*np.sin(a), r[2]]) for a in t])
ax.plot(circ[:,0], circ[:,1], ls='--', lw=1.1, color='0.6', zorder=1)

def arrow(a, b, color, lw=2.2, z=3, ms=17):
    ax.annotate('', xy=P(b), xytext=P(a),
                arrowprops=dict(arrowstyle='-|>', color=color, lw=lw, shrinkA=0,
                                shrinkB=0, mutation_scale=ms), zorder=z)

# rotation sense: small spin arc hugging the axis, just under the omega tip
SR, SZ = 0.27, 1.60
aa = np.linspace(-2.45, 1.30, 200)
sp = np.array([P([SR*np.cos(a), SR*np.sin(a), SZ]) for a in aa])
ax.plot(sp[:,0], sp[:,1], color=C_W, lw=1.6, zorder=2)
ax.annotate('', xy=sp[-1], xytext=sp[-6],
            arrowprops=dict(arrowstyle='-|>', color=C_W, lw=1.6, shrinkA=0,
                            shrinkB=0, mutation_scale=13), zorder=2)

arrow([0,0,1.20], [0,0,1.78], C_W, lw=2.6, z=4)   # omega
arrow([0,0,0], r_par, C_PAR, lw=2.2, ms=14)       # r_parallel
arrow(r_par, r, C_PER, lw=2.2)                    # r_perp
arrow([0,0,0], r, C_R, lw=2.8, z=5)               # r

w_cross_r = np.array([-r[1], r[0], 0.0])
w_cross_r = w_cross_r/np.linalg.norm(w_cross_r)*0.80
arrow(r, r + w_cross_r, C_V, lw=2.6, z=6)         # omega x r

# right-angle mark, opening away from the r_parallel arrowhead
d  = 0.115
u1 = np.array([0.0, 0.0, -1.0])
u2 = r_per/np.linalg.norm(r_per)
c  = r_par + u1*0.10
ax.plot(*zip(P(c + u1*d), P(c + u1*d + u2*d), P(c + u2*d)),
        color='0.35', lw=0.9, zorder=2)

for p in ([0,0,0], r_par, r):
    ax.plot(*P(p), 'o', ms=4.2, color='0.15', zorder=7)

def label(p, s, color, dx=0.0, dy=0.0, ha='center', va='center', fs=15):
    q = P(p); ax.text(q[0]+dx, q[1]+dy, s, color=color, fontsize=fs,
                      ha=ha, va=va, zorder=9)

label([0,0,0],      r'$O$',                            '0.15', dx=-0.11, dy=-0.13)
label([0,0,1.95],   r'$\hat{n}$',                      '0.42', dx=-0.14, dy=0.06)
label([0,0,1.26],   r'$\boldsymbol{\omega}$',          C_W,    dx=0.19, ha='left')
label(r_par*0.52,   r'$\mathbf{r}_{\parallel}$',       C_PAR,  dx=-0.15, ha='right')
label(r_par+r_per*0.5, r'$\mathbf{r}_{\perp}$',        C_PER,  dy=0.17)
label(r*0.54,       r'$\mathbf{r}$',                   C_R,    dx=0.07, dy=-0.19)
label(r+w_cross_r,  r'$\boldsymbol{\omega}\times\mathbf{r}$', C_V, dx=0.10, dy=0.05, ha='left')

ax.set_aspect('equal'); ax.axis('off')
ax.set_xlim(-1.10, 2.30); ax.set_ylim(-0.62, 2.22)
fig.tight_layout(pad=0.15)
fig.savefig('fig01.png', dpi=140, facecolor='white')
print('saved')
