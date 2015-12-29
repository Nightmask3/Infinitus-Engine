#include "Engine.h"

Engine::Engine()
{
	// WINDOW MANAGER AND WINDOW CREATION
	windowManager = new SFMLWindowManager();		 // Creates the window handler
	windowManager->CreateWin(windowManager->GetWin());// Creates the window
	// INPUT HANDLER CREATION
	inputManager = new SFMLInputManager(*windowManager);	 // Creates the input handler
	// EVENT MANAGER CREATION
	eventManager = new SFMLEventManager(*inputManager);	 // Creates the event handler
	// FRAME RATE CONTROLLER CREATION
	frameRateController = new FrameRateController(*windowManager);	// Creates the frame rate controller
	// GRAPHICS MANAGER
	graphicsManager = new OpenGLRenderer(*windowManager, *inputManager);	 // Creates the renderer
	// PHYSICS MANAGER
	physicsManager = new PhysicsManager(*frameRateController);
	// OBJECT FACTORY CREATION
	objectFactory = new GameObjectFactory(*inputManager, *graphicsManager, *physicsManager, *frameRateController); // Creates the game object factory
	// RESOURCE MANAGER CREATION
	resourceManager = new ResourceManager();
}

Engine::~Engine()
{
	/*---------------- CLEAN UP CODE ------------------ */
	delete objectFactory;
	delete graphicsManager;
	//delete frameRateController;
	delete eventManager;
	delete inputManager;
	delete windowManager;
}

void Engine::Initialize()
{
	/*--------------------------- SHADER CREATION --------------------------------*/
	graphicsManager->CreateShaderProgram();
	glUseProgram(graphicsManager->GetShaderProgram());
	if (resourceManager->ImportMapDataFromFile("Exported.txt"))
		std::cout << "Map Loaded Successfully!\n";

}

void Engine::LoadLevel()
{
	//GameObject * LoadLevel(const char *pFileName)
	//{
	//	FILE *pF;
	//	GameObject *pNewLevel = new GameObject();
	//	fopen_s(&pF, pFileName, "r"); // Reads the level file
	//	if (pF)
	//	{
	//		while (!feof(pF))
	//		{
	//			char objectName[256];
	//			memset(objectName, 0, 256 * sizeof(char));
	//		}
	//	}
	//	fclose(pF);
	//	return pNewLevel;
	//}
}

void Engine::Load()
{
	/*-- NOTE : OBJECTS MUST BE CREATED IN THE FOLLOWING ORDER! --*/
	// ORDER OF COMPONENT CREATION:
	// 1) Sprite
	// 2) Transform
	// 3) Physics
	// 4) Keyboard
	
	/*---------------------------------------- LEVEL DATA --------------------------------------------*/

	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			objectFactory->LoadObject("C:\\Users\\Nightmask3\\Documents\\Visual Studio 2013\\Projects\\Infinitus v0.0.1\\Source\\Game Object Library\\Cube.txt");
			TransformComponent * t2;
			t2 = static_cast<TransformComponent *>(objectFactory->ObjectLibrary.back().GetComponent(Component::TRANSFORM));
			t2->Translate(i, 0, j);
		}
	}
	for (int i = 0; i < resourceManager->GetMapHeight(); ++i)
	{
		for (int j = 0; j < resourceManager->GetMapWidth(); ++j)
		{
			if (resourceManager->GetMapData()[i][j] == 1)
			{
				objectFactory->LoadObject("C:\\Users\\Nightmask3\\Documents\\Visual Studio 2013\\Projects\\Infinitus v0.0.1\\Source\\Game Object Library\\Wall.txt");
				TransformComponent * t2;
				t2 = static_cast<TransformComponent *>(objectFactory->ObjectLibrary.back().GetComponent(Component::TRANSFORM));
				t2->Translate(i, 2.0f, j);
				t2->Scale(0.95, 0.95, 0.95);

				PhysicsComponent * p2;
				p2 = static_cast<PhysicsComponent *>(objectFactory->ObjectLibrary.back().GetComponent(Component::PHYSICS));
				p2->mpShape->UpdateCenter();
			}
		}
	}
	/*---------------------------------------- TEXTURE LOADING --------------------------------------------*/
	if (resourceManager->SetImage("C:\\Users\\Nightmask3\\Documents\\Visual Studio 2013\\Projects\\Infinitus v0.0.1\\sample.png"))
	{
		std::cout << "Image loaded." << std::endl;
	}
	graphicsManager->BindTexture(resourceManager->GetImage());

	if (resourceManager->SetImage("C:\\Users\\Nightmask3\\Documents\\Visual Studio 2013\\Projects\\Infinitus v0.0.1\\Menu.png"))
	{
		std::cout << "Image loaded." << std::endl;
	}
	graphicsManager->BindTexture(resourceManager->GetImage());

	if (resourceManager->SetImage("C:\\Users\\Nightmask3\\Documents\\Visual Studio 2013\\Projects\\Infinitus v0.0.1\\GameOver.png"))
	{
		std::cout << "Image loaded." << std::endl;
	}
	graphicsManager->BindTexture(resourceManager->GetImage());

	if (resourceManager->SetImage("C:\\Users\\Nightmask3\\Documents\\Visual Studio 2013\\Projects\\Infinitus v0.0.1\\GameWon.png"))
	{
		std::cout << "Image loaded." << std::endl;
	}
	graphicsManager->BindTexture(resourceManager->GetImage());
	/*---------------------------------------- OBJECT 1 - PLAYER SPHERE --------------------------------------------*/
	objectFactory->LoadObject("C:\\Users\\Nightmask3\\Documents\\Visual Studio 2013\\Projects\\Infinitus v0.0.1\\Source\\Game Object Library\\Player.txt");

	SpriteComponent * s;
	s = static_cast<SpriteComponent *> (objectFactory->ObjectLibrary.back().GetComponent(Component::SPRITE));	// Gets sprite component of game object
	
	PhysicsComponent * p;
	p = static_cast<PhysicsComponent *> (objectFactory->ObjectLibrary.back().GetComponent(Component::PHYSICS));	// Gets sprite component of game object
	p->mIsPlayer = true;


	PlayerController = static_cast<KeyboardControllerComponent *>(objectFactory->ObjectLibrary.back().GetComponent(Component::KBCONTROLLER));
	/*---------------------------------------- OBJECT 2 - ENEMY 1--------------------------------------------*/
	objectFactory->LoadObject("C:\\Users\\Nightmask3\\Documents\\Visual Studio 2013\\Projects\\Infinitus v0.0.1\\Source\\Game Object Library\\Sphere.txt");

	TransformComponent * t3;
	t3 = static_cast<TransformComponent *>(objectFactory->ObjectLibrary.back().GetComponent(Component::TRANSFORM));
	t3->Translate(15, 2, 7);
	t3->Scale(0.99, 0.99, 0.99);

	//objectFactory->CreateComponent<BehaviorComponent>();
	//b1 = static_cast<BehaviorComponent *>(objectFactory->ObjectLibrary.back().GetComponent(Component::BEHAVIOR));
	/*---------------------------------------- OBJECT 3 - ENEMY 2 --------------------------------------------*/
	objectFactory->LoadObject("C:\\Users\\Nightmask3\\Documents\\Visual Studio 2013\\Projects\\Infinitus v0.0.1\\Source\\Game Object Library\\Sphere.txt");

	TransformComponent * t4;
	t4 = static_cast<TransformComponent *>(objectFactory->ObjectLibrary.back().GetComponent(Component::TRANSFORM));
	t4->Translate(14, 4, 7);
	t4->Scale(0.99, 0.99, 0.99);
	/*---------------------------------------- OBJECT 3 - FLOOR PLANE --------------------------------------------*/
	objectFactory->CreateGameObject();

	objectFactory->CreateComponent<TransformComponent>();
	TransformComponent * tPlane;
	tPlane = static_cast<TransformComponent *>(objectFactory->ObjectLibrary.back().GetComponent(Component::TRANSFORM));
	objectFactory->CreateComponent<PhysicsComponent>();
	physicsManager->SetBoundingBoxType(Bounding::PLANE);
}

void Engine::Update()
{
	/*--------------------------- CAMERA CREATION --------------------------------*/
	Vector3D eye(0.0f, 10.0f, -10.0f, 0.0f);
	Vector3D target(0.0f, 0.0f, 1.0f, 0.0f);
	Vector3D up(0.0f, 1.0f, 0.0f, 0.0f);
	Camera EditorCamera(eye, target, up, *inputManager, *frameRateController);
	/*---------------------------------------- FRAME RATE SETTINGS --------------------------------------------*/
	frameRateController->ToggleVSync(true);
	frameRateController->EnableFrameRateLimit(60);
	/*---------------------------------------- GAME LOOP --------------------------------------------*/
	/*Vector3DSet(&target, t->mTranslation.m[0][3], t->mTranslation.m[1][3], t->mTranslation.m[2][3] + 1, 1);
	Vector3DSet(&eye, t->mTranslation.m[0][3] - 5, t->mTranslation.m[1][3], t->mTranslation.m[2][3], 1);
	Camera PlayerCamera(eye, target, up, *inputManager, *frameRateController);*/
	while (windowManager->GetWin().isOpen())
	{
		frameRateController->updateFrameTime();
		PlayerController->Update();
		if (PlayerController->mGameWon == true)
			graphicsManager->mWinScreen = true;
		/*PlayerCamera.SetCameraPos(t->mTranslation.m[0][3] - 5, t->mTranslation.m[1][3], t->mTranslation.m[2][3], 1);
		PlayerCamera.SetCameraDir(t->mTranslation.m[0][3], t->mTranslation.m[1][3], t->mTranslation.m[2][3] + 1, 1);*/
		/*PlayerCamera.Update();
		graphicsManager->CreateViewMatrix(PlayerCamera.GetCameraPos(), PlayerCamera.GetCameraDir(), PlayerCamera.GetUpVec()); */
		EditorCamera.Update();
		graphicsManager->CreateViewMatrix(EditorCamera.GetCameraPos(), EditorCamera.GetCameraDir(), EditorCamera.GetUpVec());
		physicsManager->Update();
		if (physicsManager->mGameOver)
			graphicsManager->mLoseScreen = true;
		//b1->Update();
		graphicsManager->Render();
		windowManager->GetWin().display(); // Swap buffers
		inputManager->UpdateInputState();  // Handles the input for this frame TODO : Operators for combinations of keys
		// HANDLE THE EVENTS FOR THIS GAME LOOP
		while (windowManager->GetWin().pollEvent(eventManager->GetEvent()))	// Fills out the window events into the event variable
		{
			eventManager->SetEventType();								// Finds out the event type
			eventManager->HandleEvent();								// Handles the event based on its input type
		}
		std::cout << "Frame Time : " << (frameRateController->dt);
		std::cout << "\tFrame Rate : " << (1 / frameRateController->dt) << "\r";
	}
}