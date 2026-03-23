# Space Shuttle — 3D OpenGL Model

**Iteration 2: Complete Exterior Stack**

A fully interactive 3D model of the NASA Space Shuttle stack, rendered using the OpenGL fixed-function pipeline with freeglut (C++20).

---

## Build Instructions

### Linux (Ubuntu / Debian)

```bash
# Install dependencies
sudo apt update
sudo apt install build-essential freeglut3-dev libglu1-mesa-dev

# Build
make

# Run
./shuttle
```

### macOS (Homebrew)

```bash
brew install freeglut
make PLATFORM=macos
./shuttle
```

### Windows (MSYS2 / MinGW-w64)

```bash
# In MSYS2 MinGW64 shell:
pacman -S mingw-w64-x86_64-freeglut mingw-w64-x86_64-gcc
make PLATFORM=mingw
./shuttle.exe
```

### Visual Studio 2022

1. Create an Empty C++ Project.
2. Right-click project → **Manage NuGet Packages** → Browse → install `nupengl.core`.
3. Add all `.cpp` files under `src/` to the project.
4. Set **C++ Language Standard** to **ISO C++20** in Project Properties → C/C++ → Language.
5. Set **Additional Include Directories** to `src/` in C/C++ settings.
6. Build (Ctrl+Shift+B) and run (F5).

### CMake (cross-platform)

```bash
mkdir build && cd build
cmake ..
cmake --build .
./shuttle
```

---

## Controls

| Input              | Action                                                    | Since   |
|--------------------|-----------------------------------------------------------|---------|
| Left Mouse Drag    | Orbit camera (rotate azimuth + elevation)                 | Iter 1  |
| Right Mouse Drag   | Zoom camera (drag up/down)                                | Iter 1  |
| Middle Mouse Drag  | Pan camera                                                | Iter 1  |
| Scroll Wheel       | Zoom in / out                                             | Iter 1  |
| `1`–`6`            | Preset viewpoints (front, side, aft, top, 3/4, launch)    | Iter 1  |
| `W`                | Toggle wireframe / solid rendering                        | Iter 1  |
| `A`                | Toggle axis reference lines (X=red, Y=green, Z=blue)     | Iter 1  |
| `H`                | Cycle part highlight (yellow wireframe on selected part)  | Iter 2  |
| `Esc`              | Exit                                                      | Iter 1  |

---

## What You Should See (Iteration 2)

The complete shuttle launch stack centred at the world origin:

- **Orbiter** — white tapered fuselage with dark nose cone, dark delta wings, light vertical stabilizer, dark crew cabin hump with blue windshield panes, and payload bay door seam outline on upper fuselage.
- **External Tank (ET)** — large orange cylinder with hemispherical dome cap, positioned below and slightly aft of the Orbiter, connected by two vertical attachment struts.
- **Solid Rocket Boosters (SRBs)** — two grey cylinders with wider aft skirts and cone nose caps, mounted on either side of the ET, connected by four horizontal struts each.
- **SSME Nozzles** — three dark bell-shaped engine nozzles at the aft base of the Orbiter, arranged in a triangular cluster.
- **OMS Pods** — two light pods on either side of the aft fuselage.

Press **H** to cycle the yellow highlight through each major component for inspection. The title bar shows the currently highlighted part name.

---

## Iteration 2 — What Was Added

New files: `shuttle/external_tank.cpp/.h`, `shuttle/srb.cpp/.h`, `shuttle/engines.cpp/.h`. Extended: `config.h` (added ~40 new constants for ET, SRBs, OMS, crew cabin, payload bay, struts, and highlight colour), `shuttle/orbiter.cpp` (crew cabin with windshield recesses, payload bay seam outline, SSME nozzle cluster, OMS pods), `scene.cpp/.h` (ET/SRB positioning, ET-to-Orbiter struts, SRB-to-ET struts, highlight overlay system with H-key cycling), `main.cpp` (H key binding, highlight name in title bar), `primitives.cpp` (DrawDome rewritten as proper hemisphere with triangle strips).

---

## Project Structure

```
SpaceShuttle/
├── src/
│   ├── main.cpp              # GLUT init and callbacks only
│   ├── camera.cpp / .h       # Orbit camera with mouse + presets
│   ├── scene.cpp / .h        # Top-level draw, axes, highlight system
│   ├── config.h              # ALL constants — single source of truth
│   ├── primitives.cpp / .h   # Reusable geometry wrappers
│   └── shuttle/
│       ├── orbiter.cpp / .h          # Assembles all Orbiter sub-parts
│       ├── fuselage.cpp / .h         # Tapered cylinder + nose cone
│       ├── wings.cpp / .h            # Delta wings + vertical stabilizer
│       ├── engines.cpp / .h          # SSME nozzles + OMS pods     [NEW]
│       ├── external_tank.cpp / .h    # Orange ET cylinder + dome   [NEW]
│       └── srb.cpp / .h              # SRB body + skirt + nose     [NEW]
├── Makefile
├── CMakeLists.txt
└── README.md
```

---

## Iteration Roadmap

| Iteration | Focus                                         | Status |
|-----------|-----------------------------------------------|--------|
| 1         | Scene foundation & Orbiter skeleton           | ✅ Done |
| 2         | Complete exterior stack (ET, SRBs, engines)   | ✅ Done |
| 3         | Lighting, shading & materials                 | Next   |
| 4         | Interior — flight deck, mid-deck, payload bay |        |
| 5         | Animation, HUD, starfield & polish            |        |
