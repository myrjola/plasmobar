plasmobar
=========

Xmobar-like functionality for KDE panel.

Reload with `plasmapkg -u plasmobar;kbuildsycoca4;kquitapp plasma-desktop; plasma-desktop &`

XMonad config:

```
-- Command to launch the bar.
myBar = "~/bin/writelastlinefrompipe.py /tmp/xmonadstate"

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



```

writelastlinefrompipe.py

```
#!/bin/env python3

import sys

if len(sys.argv) < 2:
    sys.exit('Usage: %s filename' % sys.argv[0])

for line in sys.stdin:
    with open(sys.argv[1], "w") as f:
        print(line, file=f)
```

TODO
====

- [ ] Come up with a better IPC, dbus would be awesome
- [ ] Mouse support
- [ ] Port to Plasma Next
