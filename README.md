# GameEngine

A lightweight game engine project designed to demonstrate basic 3D rendering, lighting models, and dynamic object management using OpenGL. 

---

## How to Compile

1. **Prerequisites**:
   - Visual Studio 2022.
   - OpenGL and GLEW installed on your system.

2. **Library Setup**:
   - Inside the project folder, create a directory named `Libraries`.
   - Place the necessary external libraries (e.g., Assimp, GLEW) into the `Libraries` folder.
   - Make sure `.dll` files for these libraries are accessible at runtime by placing them in the same folder as the executable or adding them to your system's PATH.

3. **Build Steps**:
   - Clone this repository to your local system.
   - Open the generated `.sln` file with Visual Studio and build the solution.


---

## Project Structure

The project folder should have the following structure:
```
GameEngine/ 
├── include/ 
├── src/ 
├── Shaders/ 
├── resources/ # Game assets (models, textures, shaders)
└── README.md
Libraries/ # External libraries (place here)
includes/ # External includes (place here)
```

---

## Resources

- Inside the `resources/` folder, include all required assets such as:
  - Models (e.g., `.obj`, `.fbx` files).
  - Textures (e.g., `.png`, `.jpg`).

The `resources/` folder must be downloaded from the following Google Drive link:  
**[Google Drive - Resources](https://drive.google.com/file/d/1ewfpnRrMTsbjA1n_gUqvkeduyYNK6PZ9/view?usp=drive_link)**

---

## Precompiled Libraries

To save time, precompiled libraries for Assimp, GLEW, and other dependencies are also available on Google Drive:  
**[Google Drive - Precompiled Libraries](https://drive.google.com/file/d/120xgPjFSBZ7XMlfCCpGCjXkmDU77hV6S/view?usp=drive_link)**  
**[Google Drive - Headers](https://drive.google.com/file/d/1q-EAnr3YN_mISr51N-gKVBYO7SqRKGLD/view?usp=drive_link)**

Download the files and place them in the same folder as ur project:
- `Includes` → Header files.
- `Libraries` → `.lib` and `.dll` files.

---

## Usage

1. Place all your assets inside the `resources/` folder.
2. Run the executable after building to load models and render scenes.