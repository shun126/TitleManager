<center>
<h1>Title Manager Plugin for Unreal Engine</h1>
</center>

[![Unreal Engine Supported Versions](https://img.shields.io/badge/Unreal_Engine-5.1~5.4-9455CE?logo=unrealengine)](https://www.unrealengine.com/)
[![license](https://img.shields.io/github/license/shun126/TitleManager)](https://github.com/shun126/TitleManager/blob/main/LICENSE)
[![release](https://img.shields.io/github/v/release/shun126/TitleManager)](https://github.com/shun126/TitleManager/releases)
[![downloads](https://img.shields.io/github/downloads/shun126/TitleManager/total)](https://github.com/shun126/TitleManager/releases)
[![stars](https://img.shields.io/github/stars/shun126/TitleManager?style=social)](https://github.com/shun126/TitleManager/stargazers)

**Title Manager** is an Unreal Engine plugin for managing item proficiency, category experience, and title progression.

It is designed for games where repeated use of weapons, armor, tools, items, skills, or other gameplay objects should gradually increase proficiency and unlock titles.

For example:

- A sword becomes more familiar the more it is used.
- A weapon category gains experience as the player uses weapons in that category.
- A title changes from `Beginner Swordsman` to `Sword Master` when the required experience is reached.
- Item ownership, item proficiency, category experience, and title progression can be saved and loaded.

This plugin is especially useful for RPGs, action RPGs, adventure games, survival games, training games, and any game that rewards repeated use of tools or equipment.

---

## Concept

Many games have systems where the player grows not only by level, but also by repeated use of specific items or categories.

Title Manager provides a reusable foundation for this kind of progression system.

```text
Category
  ├─ Experience
  ├─ Titles
  └─ Items
      ├─ Proficiency
      └─ Quantity
````

Example:

```text
Category: Sword
  Experience: 250
  Current Title: Sword Expert

  Items:
    Iron Sword      Proficiency: 42
    Silver Sword    Proficiency: 18
    Dragon Slayer   Proficiency: 3
```

The plugin separates **category-level growth** from **item-level proficiency**, allowing you to build flexible progression rules without hard-coding every item directly into gameplay logic.

---

## Main Features

### Category Experience

Each category can have its own experience value.

Examples:

* Sword experience
* Bow experience
* Magic experience
* Armor experience
* Potion experience
* Tool experience

Experience values are clamped by the range defined in the category data.

---

### Item Proficiency

Each item inside a category can have its own proficiency value.

Examples:

* Iron Sword proficiency
* Fire Wand proficiency
* Leather Armor proficiency
* Healing Potion proficiency
* Mining Pickaxe proficiency

This allows you to track how familiar the player is with each individual item.

---

### Title Progression

Each category can define titles that are unlocked by reaching specific experience thresholds.

Example:

| Required Experience | Title      |
| ------------------: | ---------- |
|                   0 | Beginner   |
|                 100 | Apprentice |
|                 300 | Expert     |
|                1000 | Master     |

The plugin can search the current title for a category based on its experience value.

---

### Quantity Tracking

Each item can also store a quantity value.

This is useful when you want to keep related item state in the same system, such as:

* Number of owned items
* Number of collected tools
* Inventory-like lightweight counts
* Unlock state represented by quantity

---

### Blueprint-Friendly API

The core API is exposed to Blueprints through `UTitleManagerComponent`.

Common operations include:

* Get / Set / Add category experience
* Get category experience ratio
* Get / Set / Add item proficiency
* Get item proficiency ratio
* Get / Set / Add item quantity
* Find the current title for a category
* Find the title with the highest experience
* Save and load plugin state

---

### Save / Load Support

The component provides serialization data that can be stored in your own save game system.

Typical flow:

```text
Save:
  UTitleManagerComponent::Save()
    -> Store returned data in your SaveGame object

Load:
  Read data from your SaveGame object
    -> UTitleManagerComponent::Load()
```

The plugin does not force a specific save game implementation.
You can integrate it into your existing save system.

---

## Example Use Cases

### Weapon Proficiency

Track how much each weapon has been used.

```text
Category: Sword
Items:
  Iron Sword
  Steel Sword
  Flame Sword
```

When the player attacks with `Iron Sword`, add proficiency to that item and experience to the `Sword` category.

---

### Armor Familiarity

Reward the player for using the same armor repeatedly.

```text
Category: Armor
Items:
  Leather Armor
  Chain Mail
  Knight Armor
```

Higher proficiency could reduce stamina cost, improve defensive bonuses, or unlock passive effects.

---

### Tool Progression

Useful for farming, crafting, mining, or survival games.

```text
Category: Mining Tool
Items:
  Stone Pickaxe
  Iron Pickaxe
  Mythril Pickaxe
```

The more the player uses a tool, the more efficient it becomes.

---

### Adventure Game Progression

The system does not have to be limited to RPG equipment.

Examples:

* Investigation tools
* Dialogue styles
* Character relationship categories
* Training subjects
* Collection categories
* Puzzle tools

---

## Basic Setup

### 1. Install the Plugin

Clone or copy this repository into your Unreal Engine project's `Plugins` directory.

```text
YourProject/
  Plugins/
    TitleManager/
```

Then regenerate project files and rebuild the project.

---

### 2. Enable the Plugin

Open your Unreal Engine project and enable **TitleManager** from the Plugins window.

Restart the editor if required.

---

### 3. Create a Title Manager Database

Create or assign a `TitleManagerDatabase` asset/data object depending on your project setup.

The database defines:

* Experience categories
* Experience range
* Proficiency range
* Item names
* Title thresholds

Example category:

```text
Category: Sword

Experience Range:
  0 - 9999

Proficiency Range:
  0 - 100

Items:
  Iron Sword
  Steel Sword
  Flame Sword

Titles:
  0     Beginner Swordsman
  100   Sword User
  500   Sword Expert
  1000  Sword Master
```

---

### 4. Add Title Manager Component

Add `TitleManagerComponent` to the actor that owns progression data.

Common choices:

* Player Character
* Player State
* Player Controller
* Game-specific progression actor
* Inventory owner actor

For multiplayer games, choose the owning actor carefully based on where your authoritative progression data should live.

---

## Blueprint Usage Example

When the player uses an item:

```text
CategoryName = "Sword"
ItemName     = "Iron Sword"

AddProficiency(CategoryName, ItemName, 1)
AddExperience(CategoryName, 1)
FindCategoryTitle(CategoryName)
```

You can then use the returned title in UI, save data, player status screens, or reward logic.

---

## C++ Usage Example

```cpp
UTitleManagerComponent* TitleManager = FindComponentByClass<UTitleManagerComponent>();

if (TitleManager)
{
    const FString CategoryName = TEXT("Sword");
    const FString ItemName = TEXT("Iron Sword");

    TitleManager->AddProficiency(CategoryName, ItemName, 1);
    TitleManager->AddExperience(CategoryName, 1);

    const FString CurrentTitle = TitleManager->FindCategoryTitle(CategoryName);
}
```

---

## Suggested Gameplay Integration

Title Manager only manages the data and progression state.
Your game decides what the values mean.

For example:

```text
Iron Sword proficiency 0 - 20:
  No bonus

Iron Sword proficiency 21 - 50:
  Slight damage bonus

Iron Sword proficiency 51 - 80:
  Faster attack recovery

Iron Sword proficiency 81 - 100:
  Unlock special attack
```

Or:

```text
Sword category title:
  Beginner Swordsman -> basic UI title
  Sword Expert       -> unlock advanced skill tree
  Sword Master       -> unlock achievement
```

This keeps the plugin generic while allowing each game to define its own balance.

---

## Data Model

### Experience Category

An experience category defines the progression group.

It contains:

* Experience range
* Proficiency range
* Item names
* Title definitions

---

### Title

A title defines:

* Title name
* Required experience

The current title is selected based on the category's current experience value.

---

### Proficiency Value

Each item can store:

* Proficiency
* Quantity

---

### Runtime Value

Each category stores:

* Current experience
* Per-item proficiency values

---

## Fab Version

The open-source version and the Fab version contain the same plugin.

The Fab version is provided as a convenient way to support development, similar to a donation or sponsorship.

If this plugin helps your project, purchasing it on Fab is a great way to support continued maintenance and future improvements.

You can also use the GitHub version freely under the MIT License.

Fab:
[https://fab.com/s/e63c969f23f3](https://fab.com/s/e63c969f23f3)

---

## Open Source Policy

This project is open source under the MIT License.

You may:

* Use it in personal projects
* Use it in commercial projects
* Modify it
* Fork it
* Include it in your Unreal Engine project

Please see [LICENSE](LICENSE) for details.

---

## Supported Platforms

Current plugin configuration includes:

| Module             | Type                  | Platforms      |
| ------------------ | --------------------- | -------------- |
| TitleManager       | Runtime               | Win64, Android |
| TitleManagerEditor | Editor / UncookedOnly | Win64          |

Please verify platform compatibility in your own project before shipping.

---

## Project Status

This plugin is currently small and focused.

The goal is to provide a simple, reusable foundation for:

* Item proficiency
* Category experience
* Title progression
* Lightweight progression persistence

Feedback, bug reports, documentation improvements, and pull requests are welcome.

---

## Roadmap Ideas

Possible future improvements:

* More sample Blueprints
* More sample databases
* Better editor tooling
* Improved documentation
* More gameplay examples
* Automated tests
* Example save game integration
* Example UI widget for displaying titles and proficiency
* More detailed multiplayer usage notes

Roadmap items are not guaranteed.
Please open an issue if you need a specific feature.

---

## Documentation

Current documentation resources may include:

* README
* Source code comments
* Example assets
* Doxygen configuration
* Images under the `Document` directory

More detailed documentation will be added over time.

---

## Contributing

Contributions are welcome.

Good first contributions include:

* Fixing typos
* Improving README examples
* Adding Blueprint screenshots
* Adding sample databases
* Reporting bugs
* Suggesting API improvements
* Improving comments
* Adding small tests or validation logic

Please read [CONTRIBUTING.md](CONTRIBUTING.md) before opening a pull request.

---

## Support

For bugs, feature requests, and questions, please use GitHub Issues or Discussions.

When reporting a bug, please include:

* Unreal Engine version
* Plugin version or commit hash
* Platform
* Reproduction steps
* Expected behavior
* Actual behavior
* Logs or screenshots if available

---

## License

MIT License.

See [LICENSE](LICENSE) for details.

---

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/M4M413XDXB)
