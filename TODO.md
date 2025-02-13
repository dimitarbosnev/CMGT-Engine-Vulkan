1. Add FBX import to Mesh Component
    # find fbx librry
    # Add functions to Mesh::Builder for fbx
    * See if you can extract material data from fbx to creaate materials
    * Create the special material for the mesh
3. Object and Level Serializer and Deserializer
    # Find a bit serialization library
    # make a base structure "Packet" that defines a header for seria1lized objects
    # a mechanism to trigger the correct deserializer for an object
    # make a serializer/deserializer for every obect derived class
4. Better Implementation of Lights
    # Where to store the lights (is the world object correct?) (maybe similar mechanisim to how meshes are scheduled for render)
    # how to pass multiple lights to the shaders
    # base shader file which will be included in other shaders (can it be done?)
    * Differed rendering pipeline
5. Add ImGui to the project -> might translate into making an editor
    # imgui to open with program start
    # moving existing objects through imgui
    # add objects through imgui in scene
    # add components to objcets through imgui
6. Implement Textures
    # Create a materia; that can take in textures
    # Create a texture reader using libpng
7. Implement Better Graphics Pipelines
    # Think what basic materials I am missing
    # Pipeline cashe
8. Implement proper Subscribe system
    # Reaserch why the EventType crashes
9. Implement proper Event system
    # Expand on EvenBus class
10. Add Engine Settings 
    # class which will be a Singelton which will be called by everything to check for settings
11. Finish Physics Engnie by completing the Physics Body class
    # add velosity and acceleration to  Physics Body 
    # Attach Physics Body to Collider class
    # Functions to apply force to physics body
    # detetmine body type (STATIC, DYNAMIC)
    * implement angular velosity and acceleration and functions
13. Add UI to engine viewport
    # Create a UiObject from Object class
    # Create a new shaders for UIs -> the don't need view and projection matrixes
    # create a pipeline for UIs
14. Add Ray cast to physics engine
    # add ray cast for sphere collider
    # add ray cast to capsule collider
15. Implement trigger colliders
    # seperate colliders to trigger colliders or not
16. Implemet algorithm to determine if a mesh is convex or not and seperate mesh into convex shapes
17. Implement Compute pipelines
18. Move physics engine to compute pipelines
19. Make it so all objects have the render function
20. Implemet a sky box
21. Implement Specialized constants
22. Have Fun I guess :)



NOTE: The enigne requires vc++ redistributable
NOTE: And don't forget to compile in release mode to work for other PCs