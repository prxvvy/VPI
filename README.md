# VPI (Vim Plugin installer)

This is a tool to install a bundle of plugins when first installing [my vim configs](https://github.com/prxvvy/.dotfiles/tree/master/vim).

It's suckless style written and barely any complicated programming so that anyone can hack into it.

The installer uses vim8's native plugin manager (git clone in a directory). This tool aims to automate the job of cloning each plugin github repo by yourself by just adding plugins' info, compiling and running. Give it a try.

# Installing a bunch of plugins at once

In [config.h](https://github.com/prxvvy/VPI/blob/master/config.h) header file you will find some variables the names of those are very descriptive so no need in explaining here. But I'll do it anyway in case someone's lost.

**idepluginspath**: is basically where the plugins in charge of the editor stuff like autocompletion, auto pairs and such will be installed.
**appearancepluginspath**: the same thing as **idepluginspath** variable but for plugins in charge of the editor appearance.
**separator**: This one is the separator between the plugin info. If changing this, ensure to also change it in the items of the plugins info array.
**plugins**: is a string array containing each plugin info in the following format, plugin_author separator plugin_name separator plugin_category, obviously wiht no spaces. For instance `morhetz;gruvbox;appearance`, note the ";" that's the separator, which also gotta be defined in **separator** variable as ";" since it's ";" in `morhetz;gruvbox;appearance`.

PS: In case you don't know suckless style, you gotta edit the [config.h](https://github.com/prxvvy/VPI/blob/master/config.h) header file to add plugins, for instance, recompile and run. This way the tool remains pretty minimalist.

# Usage

First off, clone this repo if haven't yet.

```shell
$ git clone https://github.com/prxvvy/VPI.git
```

There's some shell scripts you can use to build & run the binary. That's the good part, no need to build it with sudo.

**building**

```shell
$ ./build
```

This will build the binary and save it to a directory called "cmake-build-debug" but you change that, Everything is pretty hackeable!

**Running**

```shell
$ ./run
```

This will build, run the binary and save it to a directory called "cmake-build-debug" if not built yet.

**Debugging memory usage**

```shell
$ ./debug
```

This will build, run the binary with valgrind to check possibly memory leaks and save it to a directory called "cmake-build-debug" if not built yet. Oh yeah, this tool uses dynamic memory so watchout.

## Got an issue using this tool?

Feel free to open an issue.

# Contributing

There's a TODO list file you can help with.

## Licensing

`VPI` is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.
