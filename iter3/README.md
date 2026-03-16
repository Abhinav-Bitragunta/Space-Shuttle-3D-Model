# Space Shuttle — 3D OpenGL Model

**Iteration 3: Lighting, Shading & Materials**

A fully interactive 3D model of the NASA Space Shuttle stack, rendered using the OpenGL fixed-function pipeline with freeglut (C++20).

---

## Build Instructions

### Linux (Ubuntu / Debian)

```bash
sudo apt update
sudo apt install build-essential freeglut3-dev libglu1-mesa-dev
make
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
pacman -S mingw-w64-x86_64-freeglut mingw-w64-x86_64-gcc
make PLATFORM=mingw
./shuttle.exe
```

### Visual Studio 2022

1. Create Empty C++ Project → NuGet → install `nupengl.core`.
2. Add all `src/*.cpp` files. Set C++20 and `src/` as include directory.
3. Build and run.

### CMake

```bash
mkdir build && cd build && cmake .. && cmake --build . && ./shuttle
```

---

## Controls

| Input              | Action                                                    | Since   |
|--------------------|-----------------------------------------------------------|---------|
| Left Mouse Drag    | Orbit camera (rotate azimuth + elevation)                 | Iter 1  |
| Right Mouse Drag   | Zoom camera                                               | Iter 1  |
| Middle Mouse Drag  | Pan camera                                                | Iter 1  |
| Scroll Wheel       | Zoom in / out                                             | Iter 1  |
| `1`–`6`            | Preset viewpoints (front, side, aft, top, 3/4, launch)    | Iter 1  |
| `W`                | Toggle wireframe / solid                                  | Iter 1  |
| `A`                | Toggle axis reference lines                               | Iter 1  |
| `H`                | Cycle part highlight (yellow wireframe overlay)           | Iter 2  |
| `S`                | Toggle flat / smooth shading                              | Iter 3  |
| `L`                | Toggle lighting on / off                                  | Iter 3  |
| `Esc`              | Exit                                                      | Iter 1  |

---

## What You Should See (Iteration 3)

The full shuttle stack now responds to two light sources:

- **GL_LIGHT0 (Sun)** — warm directional light from upper-right, producing distinct highlights on cylindrical surfaces and specular glints on the SSME nozzles.
- **GL_LIGHT1 (Earth glow)** — subtle blue-tinted fill from below, softening shadows on the underside of the ET and SRBs.

Each component has distinct material properties: the Orbiter tiles are low-specular white/black, the ET is matte orange, the SRBs have a mid-specular metallic grey, and the SSME nozzles are dark steel with high specular highlights.

Press **S** to compare flat vs smooth shading. Press **L** to toggle lighting off and see the flat-colour fallback (same colours as Iteration 2).

---

## Iteration 3 — What Was Added

New files: `lighting.cpp/.h` (GL_LIGHT0 sun + GL_LIGHT1 earth-glow setup), `materials.cpp/.h` (15 material presets with ambient/diffuse/specular/shininess per component). Updated: `config.h` (added VSTAB_Y_BASE constant, lighting parameter arrays, user adjustments to WING_Z_ATTACH=1.5, VSTAB_Z_ATTACH=0.3, ET_OFFSET_Y=-0.68, SSME_SPACING=0.30, SSME_CLUSTER_Y=0.08), `wings.cpp` (vstab direction fix — trailing edge vertical, leading edge swept; uses VSTAB_Y_BASE instead of hardcoded 0.0), `engines.cpp` (SSME cluster centroid-centred so spacing/Y changes don't shift the group), `scene.cpp/.h` (lighting enable/disable, shading toggle, GL_COLOR_MATERIAL), `main.cpp` (S/L key bindings, setupLighting() at startup, GL_NORMALIZE enabled). All geometry files updated to call material functions instead of raw glColor.

---

## Project Structure

```
SpaceShuttle/
├── src/
│   ├── main.cpp                  # GLUT init and callbacks
│   ├── camera.cpp / .h           # Orbit camera
│   ├── scene.cpp / .h            # Top-level draw, highlight, light state
│   ├── config.h                  # ALL constants
│   ├── primitives.cpp / .h       # Geometry wrappers
│   ├── lighting.cpp / .h         # Light setup (sun + earth glow)    [NEW]
│   ├── materials.cpp / .h        # Material presets per component    [NEW]
│   └── shuttle/
│       ├── orbiter.cpp / .h
│       ├── fuselage.cpp / .h
│       ├── wings.cpp / .h
│       ├── engines.cpp / .h
│       ├── external_tank.cpp / .h
│       └── srb.cpp / .h
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
| 3         | Lighting, shading & materials                 | ✅ Done |
| 4         | Interior — flight deck, mid-deck, payload bay | Next   |
| 5         | Animation, HUD, starfield & polish            |        |
