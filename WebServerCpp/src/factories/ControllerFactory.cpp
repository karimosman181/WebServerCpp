#include <vector>
#include "BaseController.h"
#include "HomeController.h"
#include "AssetsController.h"

class ControllerFactory {
public:
    static std::vector<BaseController*> GetControllers() {
        return {
            new HomeController(),
            new AssetsController()
            // Add more controllers here
        };
    }
};
