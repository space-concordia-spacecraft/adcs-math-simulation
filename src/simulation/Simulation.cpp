#include "../../include/simulation/Simulation.h"

# define M_PI 3.141592653589793238462643383279502884L
auto rotationFactor = M_PI/128;

    Simulation* Simulation::activeSimulation = nullptr;

    Simulation::Simulation():rotation(0,0,0),cubeSat_ptr(std::make_shared<TriangleMesh>()),earth_ptr(std::make_shared<TriangleMesh>()){
        if(activeSimulation != nullptr) {
            delete activeSimulation;
        }

        activeSimulation = this;
    }

    Simulation::~Simulation(){
        if(activeSimulation == this) {
            activeSimulation = nullptr;
        }
    }
    /**
     * Initializes the Simulation by creating the Visualizer and Registering Key & Animation Callbacks.
     * @return true if successfully initialized.
     */
    bool Simulation::Initialize(){
        vis.CreateVisualizerWindow("ADCS Simulation",800.0,600.0);
        vis.AddGeometry(cubeSat_ptr);
        vis.AddGeometry(earth_ptr);
        vis.AddGeometry(coordinate_Frame);
        vis.RegisterKeyCallback(GLFW_KEY_1,rotationToggle);
        vis.RegisterKeyCallback(GLFW_KEY_2,revolutionToggle);
        vis.RegisterKeyCallback(GLFW_KEY_UP,rotateSatelliteAntiClockwise);
        vis.RegisterKeyCallback(GLFW_KEY_DOWN,rotateSatelliteClockwise);
        vis.RegisterAnimationCallback(_animationCallback);
        return true;
    }
    /**
     * Reads the meshes of the SC-ODIN , Earth and Creates a Coordinate Reference Frame.
     * @return True if completed successfully
     */
    bool Simulation::ReadMeshes() {
        if (ReadTriangleMesh("./assets/models/sc_odin_budget.ply", *this->cubeSat_ptr)) {
            LogInfo("Successfully read  CubeSat Mesh...\n");
        } else {
            LogWarning("Failed to read CubeSat Mesh...\n\n");
            return false;
        }
        cubeSat_ptr->ComputeVertexNormals();
        cubeSat_ptr->Scale(0.1,Eigen::Vector3d(0.5,1,1));
        cubeSat_ptr->Translate(Eigen::Vector3d(50,0,0));
        cubeSat_ptr->PaintUniformColor(Eigen::Vector3d(0.5568,0.5568,0.5568));


        if (ReadTriangleMesh("./assets/models/earth_mesh.ply", *this->earth_ptr)) {
            LogInfo("Successfully read Earth Mesh...\n");
        } else {
            LogWarning("Failed to read Earth Mesh...\n\n");
            return false;
        }
        earth_ptr->PaintUniformColor(Eigen::Vector3d(0.6784,0.8471,0.902));
        this->coordinate_Frame = TriangleMesh::CreateCoordinateFrame();
        coordinate_Frame->Scale(20,coordinate_Frame->GetCenter());
        LogInfo("Successfully Created Coordinate Reference Mesh...\n");
        return true;
    }
    /**
     * Reads,Initializes and Runs the simulation.
     * @return 1 if successful.
     */
    int Simulation::run() {
        LogInfo("[Boot Info]\n");
        if(ReadMeshes()){
            LogInfo("Meshes Read and Initialized Successfully...\n");
        }else{
            LogInfo("Meshes Reading and Initialization Failed...");
        }

        if(Initialize()){
            LogInfo("Simulation Successfully Initialized...\n");
        }else{
            LogInfo("Simulation Initialization Failed...");
        }

        vis.Run();

        return 0;
    }

    void Simulation::setRotation(Eigen::Vector3d &rot){
        rotation = Eigen::Vector3d(rot);
    }

    bool Simulation::animationKeyCallback(Visualizer *vis) {
        /**
         * Rotates the CubeSat on its Z-Axis.
         */
         if(activeSimulation->rotateFlag){
             cubeSat_ptr->Rotate(cubeSat_ptr->GetRotationMatrixFromXYZ(Eigen::Vector3d(0,0,rotationFactor)), cubeSat_ptr->GetCenter());
         }


        /**
         * Revolves the CubeSat around the planet.
         */
         if(activeSimulation->revolveFlag){
             cubeSat_ptr->Rotate(cubeSat_ptr->GetRotationMatrixFromXYZ(Eigen::Vector3d(0,0,rotationFactor)), earth_ptr->GetCenter());
         }
        return true;
    }

    bool Simulation::_animationCallback(Visualizer * vis) {
        if (activeSimulation != nullptr) {
            return activeSimulation->animationKeyCallback(vis);
        }
        return false;
    }


    /** Callback functions that are used for the Satellite **/

    /**
     *
     * @param vis is the application that is rendering the Simulation.
     * @return False
     */
    bool Simulation::rotationToggle(Visualizer *vis) {
        activeSimulation->rotateFlag = !(activeSimulation->rotateFlag);
        return false;
    }

    /**
     *
     * @param vis is the application that is rendering the Simulation.
     * @return False
     *
     *  This changes the flag so that the satellite can revolve around the Earth continuously.
     */
    bool Simulation::revolutionToggle(Visualizer *vis) {
        activeSimulation->revolveFlag = !(activeSimulation->revolveFlag);
        return false;
    }
    /**
     *
     * @param vis is the application that is rendering the Simulation.
     * @return False
     *
     *  This allows for the satellite to be rotated around anticlockwise by using key input.
     */
    bool Simulation::rotateSatelliteAntiClockwise(Visualizer *vis) {
        activeSimulation->cubeSat_ptr->Rotate(activeSimulation->cubeSat_ptr->GetRotationMatrixFromXYZ(Eigen::Vector3d(0,rotationFactor,0)),activeSimulation->cubeSat_ptr->GetCenter());
        return false;
    }
    /**
     *
     * @param vis is the application that is rendering the Simulation.
     * @return False
     *
     *  This allows for the satellite to be rotated around clockwise by using key input.
     */
    bool Simulation::rotateSatelliteClockwise(Visualizer *vis) {
        activeSimulation->cubeSat_ptr->Rotate(activeSimulation->cubeSat_ptr->GetRotationMatrixFromXYZ(Eigen::Vector3d(0,-rotationFactor,0)),activeSimulation->cubeSat_ptr->GetCenter());
        return false;
    }


