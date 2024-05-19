#include <ecl_ekf/ekf.h>
#include <rapidjson/document.h>

/*
Responsible for simulating _ekf prediction and estimation
*/

class ModuleSim
{
    public:
        // Load file
        ModuleSim(char * filename);

        // Run a single step of EKF loop
        void normalRunSingle(int histIndex);

        // Run through the whole history
        void normalRunAll();

        // Given attack values 
        void attackRunSingle(int histIndex);
        
        // Work on this function later
        void simulateNextStep(int histIndex);

        // Log and free memory
        void close();
        
    private:
        rapidjson::Document document; // Used to store and load ekf object
        rapidjson::Document logDocument; // Used to store logs
        Ekf _ekf;

        void _verify(rapidjson::value ekfObj);
        void _load_ekf(rapidjson::value ekfObj);
        void _logRun();
}