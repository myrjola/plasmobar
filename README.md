plasmobar
=========

Xmobar-like functionality for KDE panel.

Reload with `plasmapkg -u plasmobar;kbuildsycoca4;kquitapp plasma-desktop; plasma-desktop &`

XMonad config:

```
-- Command to launch the bar.
myBar = "cat > /tmp/xmonadfifo"

-- | Qt Rich text color formatter
qtColor :: String  -- ^ foreground color: a color name, or #rrggbb format
        -> String  -- ^ background color
        -> String  -- ^ output string
        -> String
qtColor fg bg = wrap t "</span>"
  where t = concat ["<span style='color:", fg, if null bg then "" else "; background-color: " ++ bg, "'>"]

-- Custom PP, configure it as you like. It determines what is being written to the bar.
myPP = xmobarPP {
    ppCurrent = qtColor "#429942" "" . wrap "[" "]"
  , ppTitle   = qtColor "orange" "" . shorten 80
  , ppUrgent   = qtColor "red" "yellow"
  }

main :: IO()
main = do
  replace
  xmonad =<< statusBar myBar myPP toggleStrutsKey conf {
   startupHook = startupHook conf >> setWMName "LG3D"
  }




TODO
====

- [X] Come up with a better IPC, dbus would be awesome, solved this with QThread and a C++ plasmoid
- [X] Get rid of strange characters for Konsole window title â[][]
- [ ] Mouse support
- [ ] Port to Plasma Next
