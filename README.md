# mod-ghost-mounts
 The Ghost Mounts module for AzerothCore allows players to use mounts while dead (ghosted). This feature provides a seamless experience where players can continue to use mounts in ghost form, with adjustable speeds and mount display IDs depending on their level and faction.

# Ghost Mounts Module for AzerothCore

## Description

The **Ghost Mounts** module for **AzerothCore** allows players to use mounts while dead (ghosted). This feature provides a seamless experience where players can continue to use mounts in ghost form, with adjustable speeds and mount display IDs depending on their level and faction.

- Players can mount while dead in ghost form, with mount types (ground or flying) depending on their faction (Alliance/Horde) and level.
- The module features configurable settings that allow you to modify mount display IDs and speed for different level ranges.
- Flying mounts are restricted to **Outland** and **Northrend** maps only, while ground mounts are available everywhere else.
- Configurations for mount display IDs and speeds are available through a config file (`mod_ghost_mounts.conf.dist`), making it easy to customize the module to fit your server needs.

## Features

- **Mount Display IDs**: Set different display IDs for Alliance and Horde players, both for ground and flying mounts.
- **Level-Based Speed Scaling**: Customize mount speeds based on the player's level:
  - **20-39**: Ground mount with 60% speed
  - **40-59**: Ground mount with 100% speed
  - **60-69**: Flying mount with 150% speed (only in Outland/Northrend)
  - **70-80**: Flying mount with 310% speed (only in Outland/Northrend)
- **Flying Restrictions**: Flying mounts are only allowed in **Outland** (530) and **Northrend** (571).
- **Configurable**: All settings (mount display IDs, speed, and level brackets) are customizable via the `mod_ghost_mounts.conf.dist` config file.