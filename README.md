# Graphics-API-2D-OpenGL
This is a lightweight graphics drawing library using C++ and OpenGL. GLFW is used for making a window for the drawing and GLM is the math library. The core of the project is to create a 2D renderer for 
drawing 2D graphics. There is a file called renderer that has all the componants to the renderer including the vertex buffer, index buffer, shaders (GLSL), Textures,
a windowing class, entities for drawing, and the actual renderer class that puts all of these componants together. Right now it supports drawing quads, triangles, colors, and
textures for any of those entities. There is also a basic event system that uses GLFW callbacks. So technically, a basic game might be able to be made but I haven't tried that
yet because it's not ready for that. This is closer to a library like SFML rather an a game engine like Unity or Unreal. This is my biggest project to date and I mostly doing it like practice for created a full 
game engine my self one day. So far I've learned so much about proper graphics programming concepts and the process of software engineering just with this project alone. 
