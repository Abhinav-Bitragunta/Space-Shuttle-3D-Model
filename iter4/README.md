# Space Shuttle — 3D OpenGL Model

**Iteration 4: Interior — Flight Deck, Mid-Deck & Payload Bay**

A fully interactive 3D model of the NASA Space Shuttle stack with both exterior and interior views, rendered using the OpenGL fixed-function pipeline with freeglut (C++20).

---

## Build Instructions

### Linux (Ubuntu / Debian)

```bash
sudo apt update
sudo apt install build-essential freeglut3-dev libglu1-mesa-dev
make
./shuttle
```

### macOS

```bash
brew install freeglut
make PLATFORM=macos
./shuttle
```

### Windows (MSYS2)

```bash
pacman -S mingw-w64-x86_64-freeglut mingw-w64-x86_64-gcc
make PLATFORM=mingw
./shuttle.exe
```

### Visual Studio 2022

NuGet `nupengl.core`, add all `src/*.cpp`, set C++20, include `src/`.

### CMake

```bash
mkdir build && cd build && cmake .. && cmake --build . && ./shuttle
```

---

## Controls

| Input              | Action                                          | Since   |
|--------------------|-------------------------------------------------|---------|
| Left Mouse Drag    | Orbit camera (exterior only)                    | Iter 1  |
| Right Mouse Drag   | Zoom camera (exterior only)                     | Iter 1  |
| Middle Mouse Drag  | Pan camera (exterior only)                      | Iter 1  |
| Scroll Wheel       | Zoom in/out (exterior only)                     | Iter 1  |
| `1`–`6`            | Preset viewpoints (exterior only)               | Iter 1  |
| `W`                | Wireframe toggle (exterior) / Walk forward (interior) | Iter 1/4 |
| `A`                | Axis toggle (exterior) / Strafe left (interior) | Iter 1/4 |
| `S`                | Shading toggle (exterior) / Walk backward (interior) | Iter 3/4 |
| `D`                | Strafe right (interior only)                    | Iter 4  |
| Mouse movement     | Look around (interior only)                     | Iter 4  |
| `H`                | Cycle part highlight (exterior only)            | Iter 2  |
| `L`                | Toggle lighting on/off                          | Iter 3  |
| `F`                | Toggle exterior / interior camera mode          | Iter 4  |
| `O`                | Open / close payload bay doors (animated)       | Iter 4  |
| `Esc`              | Return to exterior (if interior) / Exit         | Iter 1/4 |

---

## What You Should See (Iteration 4)

### Exterior View (default)
The complete shuttle stack with all Iter 1–3 features. Press **O** to watch the payload bay doors swing open with smooth animation, revealing the interior structural framework.

### Interior View (press F)
The cursor locks and you enter first-person mode inside the flight deck:

- **Flight deck** — Two pilot seats with backrests and legs, a centre console, side consoles along the walls. The forward instrument panel displays a 4×6 grid of coloured gauges (green, amber, blue, red, teal, purple) with metal bezels. An overhead panel has a grid of glowing coloured switch indicators. Structural windshield frames divide the forward window into panes.
- **Mid-deck** (below flight deck) — Walk down to see wall lockers with handles on both sides, a floor panel grid, and a structural hatch frame in the floor.
- **Warm cabin lighting** — GL_LIGHT2 provides warm point-source illumination that attenuates with distance, creating a cozy cockpit feel distinct from the exterior sun/earth lights.

Press **Esc** to return to exterior orbit view.

---

## Iteration 4 — What Was Added

New files: `shuttle/interior/flight_deck.cpp/.h` (seats, instrument panel with 24 coloured gauges, centre/side consoles, overhead switch panel with emissive LEDs, windshield frames), `shuttle/interior/mid_deck.cpp/.h` (wall lockers with handles, floor grid, floor hatch), `shuttle/interior/payload_bay.cpp/.h` (longerons, structural frames, animated door panels with interior ribs). Updated: `config.h` (~60 new constants for interior geometry, cabin light, interior camera, door animation), `camera.cpp/.h` (full interior FPS camera with WASD walk, mouse-look via glutPassiveMotionFunc, glutWarpPointer cursor lock, toggleMode), `lighting.cpp/.h` (GL_LIGHT2 warm cabin point light with attenuation), `materials.cpp/.h` (12 new interior materials + matGauge with 8-colour cycle + matOverheadSwitch with emissive glow), `orbiter.cpp` (integrates interior rendering when in interior mode, payload bay doors always drawn, bay interior visible when doors > 5°), `scene.cpp/.h` (door animation via glutTimerFunc at 16ms ticks, gInteriorMode/gDoorAngle globals, cabin light enable/disable), `main.cpp` (F/O keys, WASD context-dependent, passiveMotionFunc, interior FOV=70° and near-clip=0.01).

---

## Project Structure

```
SpaceShuttle/
├── src/
│   ├── main.cpp
│   ├── camera.cpp / .h
│   ├── scene.cpp / .h
│   ├── config.h
│   ├── primitives.cpp / .h
│   ├── lighting.cpp / .h
│   ├── materials.cpp / .h
│   └── shuttle/
│       ├── orbiter.cpp / .h
│       ├── fuselage.cpp / .h
│       ├── wings.cpp / .h
│       ├── engines.cpp / .h
│       ├── external_tank.cpp / .h
│       ├── srb.cpp / .h
│       └── interior/                         [NEW]
│           ├── flight_deck.cpp / .h
│           ├── mid_deck.cpp / .h
│           └── payload_bay.cpp / .h
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
| 4         | Interior — flight deck, mid-deck, payload bay | ✅ Done |
| 5         | Animation, HUD, starfield & polish            | Next   |
