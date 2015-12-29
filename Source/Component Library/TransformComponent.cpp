#include "PhysicsComponent.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent() : Component(ComponentType::TRANSFORM)
{
	Matrix3DIdentity(&mTranslation); 
	Matrix3DIdentity(&mRotation); 
	Matrix3DIdentity(&mScale); 

	/*-------------------------------- MODEL MATRIX -------------------------------*/
	// Creates the translation matrix
	Matrix3DTranslate(&mTranslation, 0, 0, 0);
	// Creates the rotation matrix
	Matrix3DRotRadZ(&mRotation, 0);
	// Creates the scaling matrix
	Matrix3DScale(&mScale, 1, 1, 1);
	mOriginalScale.x = 1.05;
	mOriginalScale.y = 1.05;
	mOriginalScale.z = 1.05;

}
TransformComponent::~TransformComponent() {}

void TransformComponent::Serialize(std::string & Contents, unsigned int & Count)
{
	unsigned char tempC;
	unsigned int tempI = 0;
	std::string::size_type end;			// size_type is a typedef-ed type that is used to guarantee that no matter how large the size of the input file, it can be contained (example : if larger than int)
	std::string DataType;				// Used to check the type of data being supplied before adding to corresponding list
	std::string TempData;				// Used to get the different vertex properties into their respective list
	std::string Token = "";
	std::string TempLine = "";
	GLfloat Array[3];					// Used to hold the X, Y and Z values of the properties
	GLfloat TempFloat = 0.0f;
	DataType.reserve(64);
	Count += 5;
	while (Contents.at(Count) != '\0')
	{
		while ((Contents.at(Count) != '\r')) // Reads character by character until new line
		{
			tempC = Contents.at(Count++);
			DataType += tempC;				// Gets type of component to create
		}
		Count += 2;										// To skip the \r, \n and the '{' and its \r and \n
		end = Contents.find('\n', Count);				// Finds the end of the current vertex property array
		TempData = Contents.substr(Count, end - Count); // Second parameter is the length of the string
		std::istringstream TempStream(TempData);		// Gets a string stream constructed from the temp data string

		while (std::getline(TempStream, Token, ','))
		{
			TempFloat = strtof(Token.c_str(), NULL);
			Array[tempI++] = TempFloat;
		}
	
		if (strcmp(DataType.c_str(), "Position") == 0)
		{
			Translate(Array[0], Array[1], Array[2]);
		}
		else if (strcmp(DataType.c_str(), "Rotation") == 0)
		{
			Rotate(Array[0], Array[1], Array[2]);
		}
		else if (strcmp(DataType.c_str(), "Scale") == 0)
		{
			Scale(Array[0], Array[1], Array[2]);
		}
		Count = end + 1; // To skip the \r and \n characters
		if (Contents.at(Count) == '}') // Serialization of this component complete
		{
			Count += 3;
			return;
		}
		if (Contents.at(Count) == '-')
		{
			Count += 3;
			return;
		}
		if (Count > Contents.size())	// End of file
		{
			return;
		}
		DataType = "";
		TempLine = "";
		Token = "";
		tempI = 0;
	}
}

void TransformComponent::Update()
{
	// Transform Component does not update itself!
}

void TransformComponent::Translate(float X, float Y, float Z)
{
	mTranslation.m[0][3] += X;
	mTranslation.m[1][3] += Y;
	mTranslation.m[2][3] += Z;


	PhysicsComponent * p = nullptr;
	p = static_cast<PhysicsComponent *>(mOwner->GetComponent(Component::PHYSICS));
	if (p != nullptr)
		Vector3DSet(&p->mPositionCurr, mTranslation.m[0][3], mTranslation.m[1][3], mTranslation.m[2][3], 1);
}
void TransformComponent::Rotate(float AngleX, float AngleY, float AngleZ)
{
	if (AngleX != 0)
		Matrix3DRotRadX(&mRotation, AngleX);
	if (AngleY != 0)
		Matrix3DRotRadY(&mRotation, AngleY);
	if (AngleZ != 0)
		Matrix3DRotRadZ(&mRotation, AngleZ);
}
void TransformComponent::Scale(float X, float Y, float Z)
{
	// Saved for use in bounding box construction
	mOriginalScale.x = mScale.m[0][0];
	mOriginalScale.y = mScale.m[1][1];
	mOriginalScale.z = mScale.m[2][2];

	mScale.m[0][0] = X;
	mScale.m[1][1] = Y;
	mScale.m[2][2] = Z;
}

void TransformComponent::ScaleWithCollider(float X, float Y, float Z)
{
	// Saved for use in bounding box construction
	mOriginalScale.x = X + 0.05;
	mOriginalScale.y = Y + 0.05;
	mOriginalScale.z = Z + 0.05;

	mScale.m[0][0] = X;
	mScale.m[1][1] = Y;
	mScale.m[2][2] = Z;
}