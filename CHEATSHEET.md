# Cheat sheet

This is a document created for me, who often forgets how to manage a blog.

## How to create a new category

- Create a directory (e.g. `./docs/new-category`)
- Create a markdown file for the category (e.g. `./docs/new-category/new-category.md`)
- Fill the created category markdown as following template:
  ```bash
  ---
  layout: default
  title: Category title         # This will be key if this category.
  nav_order: 4                  # This numeric value determines the order of category.
  has_children: true            # True if you want to make children posts under this category.
  permalink: /docs/new-category # This will be used as link address between pages.
  ---

  # New category

  Blah Blah Blah ...
  ```

## How to create a new post

- Create a directory (e.g. `./docs/new-category/new-post`)
- Create a markdown file for the pose (e.g. `./docs/new-category/new-post/new-post.md`)
- Fill the created post markdown as following template:
  ```bash
  ---
  title: Post title
  layout: default
  parent: Category title # String key of the parent category.
  permalink: /docs/new-category/new-post # This will be used as link address between pages.
  ---
  
  # New post

  Blah Blah Blah ...

  # This is for comment.
  <script src="https://utteranc.es/client.js"
        repo="i-am-wonseoklee/i-am-wonseoklee.github.io"
        issue-term="pathname"
        theme="github-dark-orange"
        crossorigin="anonymous"
        async>
  </script>
  ```

## Frequently used feature

### Mathematical equations

- Use latex syntax that starts with `$$` and ends with `$$`.

### Labels

- For example, `Hello{: .label }`.

### Callouts

- Purple callout : starts with `{: .highlight }` and writes contents inside `>` (indentation).

- Yellow callout : starts with `{: .note }` and writes contents inside `>` (indentation).

### Links between posts

- Use permalink. For example, `[](/docs/new-category/new-post/new-post.md)`.

## Page preview

- `sudo apt install ruby-rubygems` (just once).
- `sudo gem install bundler jekyll` (just once).
- `sudo apt install ruby-dev` (just once).
- `cd {REPO_DIRECTORY}`
- `sudo bundle install`
- `bundle exec jekyll serve`
