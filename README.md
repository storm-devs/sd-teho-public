# Sea Dogs: To Each His Own
This repository contains game scripts and configuration files for the [Sea Dogs: To Each His Own](https://store.steampowered.com/app/223330) game.

[![Join the chat at https://discord.gg/jmwETPGFRe](https://img.shields.io/discord/353218868896071692?color=%237289DA&label=storm-devs&logo=discord&logoColor=white)](https://discord.gg/jmwETPGFRe)

 * [GitHub Discussions](https://github.com/storm-devs/sd-teho-public/discussions)
 * [Discord Chat](https://discord.gg/jmwETPGFRe)

<p align="center">
<img src="https://cdn.cloudflare.steamstatic.com/steam/apps/223330/extras/preview12.jpg">
</p>

## Running the game from Visual Studio

**To be able to run the game you need assets that go together with the game on Steam.**

0. Copy the `resource` folder from the game distribution to the root of this repository.
1. Delete the `resource/ini` folder.
2. Rename the `resource/ini_rus` or `resource/ini_eng` folder to `resource/ini`.
3. Clone the [storm-engine](https://github.com/storm-devs/storm-engine) repository.
4. Follow the steps to build the game engine.
5. Add new debug configuration for the `engine` target.
6. Set the root of this repository as the current directory: `"currentDir": "<SD-TEHO-ROOT>"`.
7. Run the game from VS.

## Contributing
If you'd like to get involved, don't hesitate to contact us. Pull requests and any other kind of help are more than welcome as well.

## License
[GPL-3.0 License](https://choosealicense.com/licenses/gpl-3.0/)