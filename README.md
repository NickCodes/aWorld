aWorld
======

C++/OGRE3D realtime 3D environment

This is a personal project using OGRE3D to bring a virtual world to life. This is a project that is going through
a phase of refactoring and library reconsideration. Plenty of background information can be obtained via the OGRE3D wiki. 

http://www.ogre3d.org/tikiwiki/tiki-index.php

Features:
- Program operation and resources are configurable in program or via external .cfg files
- Terrain creation from height maps and textures (using L3DT)
- Terrain loading from binary data files
- Parsing of complex .scene files composed of .mesh files, exportable from Blender
- Graphical overlay and menu support
- Mouse based camera rotation
- Keyboard based camera movement
- Skybox implementation
- Spatial sound treatments (location, intensity) based on the Irrklang library

Planned features:
- Non static geometry
- Mesh collision detection
- Basic physics (bullet)
- AI entity behaviors
- Interactive day/night cycle
- Dynamic weather effects
