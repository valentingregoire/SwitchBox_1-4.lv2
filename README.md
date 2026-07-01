# SwitchBox_1-4.lv2

This is an lv2 plugin that allows you to route your signal to one of 4 outputs.
This plugin is very similar to MOD's [SwitchTrigger4](https://github.com/mod-audio/mod-utilities/tree/master/SwitchTrigger4),
but with the benefit that the current selected channel is persisted in snapshots.

## Install

Just run the `install.sh` script on the device you wish to use this on:

```sh
./install.sh
```

This will use the `Makefile` to:

1. remove old installations of this plugin
2. build the plugin
3. install it into the plugins folder

If you want to install it into a different location, you can edit the
`INSTALL_PATH` in the `Makefile` on top.

## Tested

I have test the plugin on my Fedora workstation with MOD Desktop, and on my
Raspberry Pi 5.
