#ifndef HVSCENEDECLARATIONS_H
#define HVSCENEDECLARATIONS_H

#include <map>
#include <vector>
#include "hvTypes.h"
#include "hvscene.h"
#include "hvldwscene.h"
#include "hvbsdscene.h"
#include "hvfcwscene.h"

#define DECLARE_SCENE(name)     std::pair<hvString, hvScene *>(""#name"", new hv##name##Scene()),
#define START_DECLARE_PROJECT_FUNCTIONS         std::vector <std::map<hvString, hvScene*>> g_vmScreenScenes = {
#define START_DECLARE_SCENES(n)               {
#define END_DECLARE_SCENES(n)                 },
#define END_DECLARE_PROJECT_FUNCTIONS         };



START_DECLARE_PROJECT_FUNCTIONS


/*****************   SCREEN  A   SCENES     ************************/
START_DECLARE_SCENES(A)
DECLARE_SCENE(LDW)
DECLARE_SCENE(BSD)
DECLARE_SCENE(FCW)

END_DECLARE_SCENES(A)
/*****************   SCREEN  A   SCENES     ************************/



/*****************   SCREEN  B   SCENES     ************************/
START_DECLARE_SCENES(B)


END_DECLARE_SCENES(B)
/*****************   SCREEN  B   SCENES     ************************/



/*****************   SCREEN  C   SCENES     ************************/
START_DECLARE_SCENES(C)


END_DECLARE_SCENES(C)
/*****************   SCREEN  C   SCENES     ************************/


END_DECLARE_PROJECT_FUNCTIONS





#define SCENES_IN_SCREEN(n)     g_vmScreenScenes[n]
#endif // HVSCENEDECLARATIONS_H
