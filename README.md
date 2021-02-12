# Sea Dogs: To Each His Own
This repository contains localized game scripts and configuration files for [Sea Dogs: To Each His Own](https://store.steampowered.com/app/223330).

[![Join the chat at https://discord.gg/jmwETPGFRe](https://img.shields.io/discord/353218868896071692?color=%237289DA&label=storm-devs&logo=discord&logoColor=white)](https://discord.gg/jmwETPGFRe)

 * [GitHub Discussions](https://github.com/storm-devs/sd-teho-public/discussions)
 * [Discord Chat](https://discord.gg/jmwETPGFRe)

<p align="center">
<img src="https://cdn.cloudflare.steamstatic.com/steam/apps/223330/extras/preview12.jpg">
</p>

Branches:
* `develop-eng` - the latest version of English files.
* `develop-rus` - the latest version of Russian files.

## Running the game from Visual Studio

**To be able to run the game you need assets that go together with the game on Steam.**

1. Clone the [storm-engine](https://github.com/storm-devs/storm-engine) repository.
2. [Follow the steps](https://github.com/storm-devs/storm-engine#building-the-project) to build the game engine.
3. [Add new debug configuration](https://docs.microsoft.com/en-us/cpp/build/configure-cmake-debugging-sessions) for the `engine` target.
4. Set the game installation folder as the current directory in launch.vs.json, e.g. `"currentDir": "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Sea Dogs To Each His Own"`.
5. Copy the content of this repository to the game installation folder replacing existing files.
6. Run the game from VS.

## Contributing
If you'd like to get involved, don't hesitate to contact us. Pull requests and any other kind of help are more than welcome as well.

## License
[GPL-3.0 License](https://choosealicense.com/licenses/gpl-3.0/)
