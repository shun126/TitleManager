# Contributing to Title Manager

Thank you for your interest in contributing to Title Manager.

Title Manager is an Unreal Engine plugin for managing item proficiency, category experience, quantity, and title progression.

Contributions are welcome, especially documentation improvements, bug reports, Blueprint examples, sample data, and small focused code improvements.

---

## Project Philosophy

This plugin should stay simple, reusable, and game-agnostic.

The plugin should not assume one specific game genre or balance rule.

Good design direction:

- Keep the core system generic.
- Let each game decide how proficiency and titles affect gameplay.
- Keep Blueprint usage simple.
- Keep save/load integration flexible.
- Avoid adding large gameplay-specific systems directly into the plugin.

For example, the plugin may store `Sword` experience and `Iron Sword` proficiency, but it should not hard-code a damage formula for swords.

---

## Ways to Contribute

You can contribute by:

- Reporting bugs
- Improving documentation
- Adding usage examples
- Adding Blueprint screenshots
- Adding sample Title Manager databases
- Improving C++ comments
- Improving editor usability
- Suggesting API improvements
- Fixing small issues
- Testing on different Unreal Engine versions or platforms

Small, focused contributions are preferred.

---

## Before Opening an Issue

Please check existing issues first to avoid duplicates.

When opening a bug report, include:

- Unreal Engine version
- Plugin version or commit hash
- Operating system
- Target platform
- Whether the issue happens in Blueprint, C++, or both
- Reproduction steps
- Expected behavior
- Actual behavior
- Logs, screenshots, or a minimal sample project if possible

A good bug report should make it possible to reproduce the issue.

---

## Feature Requests

Feature requests are welcome.

Please describe:

- What problem you are trying to solve
- Why the current plugin cannot solve it
- How the feature should work
- Whether it should be C++, Blueprint, editor-only, or runtime
- Whether it affects save data compatibility

Please keep feature requests focused on the plugin's core purpose:

- Experience
- Proficiency
- Quantity
- Titles
- Data editing
- Save/load support
- Blueprint/C++ usability

Large gameplay systems may be better implemented in your own project rather than inside this plugin.

---

## Pull Request Guidelines

Before creating a pull request:

1. Fork the repository.
2. Create a feature branch.
3. Make a focused change.
4. Build the plugin.
5. Test the changed behavior.
6. Update documentation if needed.
7. Open a pull request with a clear description.

Recommended branch names:

```text
fix/experience-clamp
docs/readme-example
feature/sample-database
refactor/title-search
````

---

## Pull Request Scope

Please keep pull requests small.

Good pull request examples:

* Fix a typo in README
* Add a Blueprint usage screenshot
* Fix an incorrect clamp result
* Improve a function comment
* Add a simple sample database
* Improve an error message
* Add a small helper function

Avoid mixing unrelated changes.

For example, do not combine documentation rewrites, API changes, formatting changes, and sample content in one pull request.

---

## Coding Style

Please follow the existing Unreal Engine C++ style used in the project.

General rules:

* Use Unreal Engine types where appropriate.
* Keep Blueprint-facing names clear.
* Prefer explicit and readable code.
* Avoid unnecessary dependencies.
* Avoid game-specific logic in the plugin core.
* Keep public API changes intentional.
* Add comments when behavior may not be obvious.

---

## Blueprint API Guidelines

When adding or changing Blueprint-callable functions:

* Use clear function names.
* Use stable category names.
* Keep parameter names understandable.
* Avoid surprising side effects.
* Return useful values where appropriate.
* Consider how the node will look in Blueprint.
* Update README examples if the usage changes.

Blueprint usability is important for this plugin.

---

## Data Compatibility

Please be careful with save/load related changes.

Changes to serialized data may affect existing projects.

If your pull request changes save data structures, please explain:

* What changed
* Why it changed
* Whether old save data is still compatible
* Whether migration is required

Breaking save compatibility should be avoided unless clearly necessary.

---

## Testing

At minimum, please test the affected behavior manually in Unreal Engine.

Recommended checks:

* Plugin compiles
* Editor opens without plugin errors
* TitleManagerComponent can be added to an actor
* Category experience can be added
* Item proficiency can be added
* Quantity can be changed
* Current title can be found
* Save and Load work as expected
* Blueprint nodes are usable if affected

If your change affects platform-specific behavior, please mention which platform you tested.

---

## Documentation Contributions

Documentation contributions are highly appreciated.

Useful documentation improvements include:

* Better README examples
* Screenshots
* Blueprint node examples
* Sample database setup
* Save/load tutorial
* C++ usage examples
* Common mistakes
* FAQ
* Multiplayer notes

When adding images, place them in an appropriate documentation or resource directory and reference them from README or another Markdown file.

---

## Commit Message Style

Please use clear commit messages.

Examples:

```text
Fix experience clamp when category is missing
Add Blueprint example for item proficiency
Improve README setup instructions
Add sample title database
```

Commit messages do not need to follow a strict convention, but they should explain the change.

---

## Review Policy

Pull requests may be reviewed for:

* Correctness
* Simplicity
* Blueprint usability
* Compatibility
* Documentation quality
* Fit with the plugin's scope

A pull request may be declined if it adds too much game-specific behavior or makes the plugin harder to maintain.

---

## License

By contributing to this repository, you agree that your contributions will be licensed under the same license as the project.

This project uses the MIT License.

See [LICENSE](LICENSE) for details.

---

## Support the Project

The GitHub version and Fab version contain the same plugin.

The Fab version is available as a way to support development, similar to a donation or sponsorship.

If you want to support continued maintenance, documentation, and improvements, purchasing the Fab version is appreciated.

Fab:
[https://fab.com/s/e63c969f23f3](https://fab.com/s/e63c969f23f3)
