#include "SpriteComponent.h"
#include "..\Physics Library\BoundingSphere.h"
#include "..\Physics Library\BoundingBox.h"

#include "PhysicsComponent.h"
void PhysicsComponent::Serialize(std::string & Contents, unsigned int & Count)
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

		if (strcmp(DataType.c_str(), "Velocity") == 0)
		{
			Vector3DSet(&mVelocity, Array[0], Array[1], Array[2], 1);
		}
		else if (strcmp(DataType.c_str(), "Momentum") == 0)
		{
			Vector3DSet(&mMomentum, Array[0], Array[1], Array[2], 1);
		}
		else if (strcmp(DataType.c_str(), "Force") == 0)
		{
			Vector3DSet(&mForce, Array[0], Array[1], Array[2], 1);
		}
		else if (strcmp(DataType.c_str(), "Mass") == 0)
		{
			mMass = Array[0];
		}
		else if (strcmp(DataType.c_str(), "Collider") == 0)
		{
			TransformComponent * transform = nullptr;
			SpriteComponent * sprite = nullptr;
			VertexCollider temp;
			if (Array[0] == 0)
			{
				// Sphere Collider
				transform = static_cast<TransformComponent *>(mOwner->GetComponent(Component::TRANSFORM));
				sprite = static_cast<SpriteComponent *>(mOwner->GetComponent(Component::SPRITE));
				Vector3D center;
				Vector3DSet(&center, transform->mTranslation.m[0][3], transform->mTranslation.m[1][3], transform->mTranslation.m[2][3], 1);
				mpShape = new BoundingSphere(center);
				mpShape->mOwner = this;
				// Sets values of collider bounding box
				for (int i = 0; i < sprite->GetVertexList().size(); i++)
				{
					temp.X = sprite->GetVertexList()[i].X;
					temp.Y = sprite->GetVertexList()[i].Y;
					temp.Z = sprite->GetVertexList()[i].Z;
					// All debug bounding shapes are green by default (assumes that they are not colliding in first frame)
					temp.R = 0;
					temp.G = 0;
					temp.B = 1;
					temp.A = 0.5;
					temp.U = 0;
					temp.V = 0;
					VertexList.push_back(temp);
				}
				for (int i = 0; i < sprite->GetIndexList().size(); i++)
				{
					unsigned int temp = sprite->GetIndexList()[i];
					IndexList.push_back(temp);
				}

			}
			if (Array[0] == 1)
			{
				// AABB Collider
				transform = static_cast<TransformComponent *>(mOwner->GetComponent(Component::TRANSFORM));
				sprite = static_cast<SpriteComponent *>(mOwner->GetComponent(Component::SPRITE));

				Vector3D begin(sprite->GetVertexList().front().X, sprite->GetVertexList().front().Y, sprite->GetVertexList().front().Z, 1);
				Vector3D end(sprite->GetVertexList().back().X, sprite->GetVertexList().back().Y, sprite->GetVertexList().back().Z, 1);
				Vector3D center;
				
				Vector3DSet(&center, transform->mTranslation.m[0][3], transform->mTranslation.m[1][3], transform->mTranslation.m[2][3], 1);
				mpShape = new BoundingBox(begin, end);
				mpShape->mOwner = this;
				BoundingBox * box = static_cast<BoundingBox *>(mpShape);
				box->SetCenter(center);
				for (int i = 0; i < sprite->GetVertexList().size(); i++)
				{
					temp.X = sprite->GetVertexList()[i].X;
					temp.Y = sprite->GetVertexList()[i].Y;
					temp.Z = sprite->GetVertexList()[i].Z;
					// All debug bounding shapes are blue by default (assumes that they are not colliding in first frame)
					temp.R = 0;
					temp.G = 0;
					temp.B = 1;
					temp.A = 0.5;
					temp.U = 0;
					temp.V = 0;
					VertexList.push_back(temp);
				}
			}
			// CONFINES THE COLLIDER COMPONENT TO ALWAYS BE AT THE END OF THE PHYSICS COMPONENTS SPECIFICATIONS
			Count += 6;
		}
		
		if (Count >= Contents.size() || Contents.at(Count) == '-')// Serialization of this component complete
		{
			return;
		}
		if (Contents.at(Count) == '}')
		{
			Count += 5;
			return;
		}
		Count = end + 1; // To skip the \r and \n characters
		DataType = "";
		TempLine = "";
		Token = "";
		tempI = 0;
	}

}
void PhysicsComponent::Integrate(double t, double dt)
{
	Derivative a, b, c, d;
	Vector3DSet(&mPositionPrev, mPositionCurr.x, mPositionCurr.y, mPositionCurr.z, 1);
	// Finds 4 derivatives
	a = Evaluate(t, 0.0f, Derivative());
	b = Evaluate(t, dt*0.5f, a);
	c = Evaluate(t, dt*0.5f, b);
	d = Evaluate(t, dt, c);
	// Finds weighted sum of derivatives for each:

	// Position from velocity
	float dxdt = 1.0f / 6.0f *
		(a.mDerivedVelocity.x + 2.0f*(b.mDerivedVelocity.x + c.mDerivedVelocity.x) + d.mDerivedVelocity.x);

	float dydt = 1.0f / 6.0f *
		(a.mDerivedVelocity.y + 2.0f*(b.mDerivedVelocity.y + c.mDerivedVelocity.y) + d.mDerivedVelocity.y);
	
	float dzdt = 1.0f / 6.0f *
		(a.mDerivedVelocity.z + 2.0f*(b.mDerivedVelocity.z + c.mDerivedVelocity.z) + d.mDerivedVelocity.z);
	// Velocity from acceleration
	float dvxdt = 1.0f / 6.0f *
		(a.mDerivedAcceleration.x + 2.0f*(b.mDerivedAcceleration.x + c.mDerivedAcceleration.x) + d.mDerivedAcceleration.x);

	float dvydt = 1.0f / 6.0f *
		(a.mDerivedAcceleration.y + 2.0f*(b.mDerivedAcceleration.y + c.mDerivedAcceleration.y) + d.mDerivedAcceleration.y);

	float dvzdt = 1.0f / 6.0f *
		(a.mDerivedAcceleration.z + 2.0f*(b.mDerivedAcceleration.z + c.mDerivedAcceleration.z) + d.mDerivedAcceleration.z);

	// Change position and velocity accordingly
	mPositionCurr.x += dxdt * dt;
	mPositionCurr.y += dydt * dt;
	mPositionCurr.z += dzdt * dt;

	mVelocity.x += dvxdt * dt;
	mVelocity.y += dvydt * dt;
	mVelocity.z += dvzdt * dt;
	// Cap the max velocity
	mVelocity.y *= 0.99f;
}

void PhysicsComponent::UpdateTransform()
{
	TransformComponent * t = nullptr;
	t = static_cast<TransformComponent *>(mOwner->GetComponent(Component::TRANSFORM));
	t->mTranslation.m[0][3] = mPositionCurr.x;
	t->mTranslation.m[1][3] = mPositionCurr.y;
	t->mTranslation.m[2][3] = mPositionCurr.z;
	if (mpShape->mType == Bounding::SPHERE)
	{
		BoundingSphere * s = static_cast<BoundingSphere *>(mpShape);
		s->SetCenter(mPositionCurr);
	}
}

void PhysicsComponent::Recalculate()
{
	mVelocity.x = mMomentum.x * mInverseMass;
	mVelocity.y = mMomentum.y * mInverseMass;
	mVelocity.z = mMomentum.z * mInverseMass;
}

PhysicsComponent::Derivative PhysicsComponent::Evaluate(double t, double dt, const Derivative &d)
{
	Vector3D positionTemp, velocityTemp;

	positionTemp = mPositionCurr;
	positionTemp.x += d.mDerivedVelocity.x * dt;
	positionTemp.y += d.mDerivedVelocity.y * dt;
	positionTemp.z += d.mDerivedVelocity.z * dt;

	velocityTemp = mVelocity;
	velocityTemp.x += d.mDerivedAcceleration.x * dt;
	velocityTemp.y += d.mDerivedAcceleration.y * dt;
	velocityTemp.z += d.mDerivedAcceleration.z * dt;
	
	Derivative output;
	output.mDerivedVelocity = velocityTemp;
	// If acceleration is turned off, do not calculate anymore
	if (mAcceleration == true)
		output.mDerivedAcceleration = Acceleration(t + dt);
	else
		Vector3DZero(&output.mDerivedAcceleration);
	return output;
}

Vector3D PhysicsComponent::Acceleration(float t)
{
	Vector3D output;
	Vector3DZero(&output);
	const float k = 10;
	output.y = -k * t;
	// Caps the max falling speed
	if (abs(output.y) > 10)
		output.y = -10;
	return output;
}

void PhysicsComponent::HandleEvent(Event * pEvent)
{
	// If a collide event
	if (pEvent->mType == EventType::COLLIDE)
	{
		// Change color values as necessary
		for (int i = 0; i < VertexList.size(); i++)
		{
			if (mpShape->mType == Bounding::AABB)
			{
				VertexList[i].B = 1;
				VertexList[i].G = 1;
			}
			else
			{
				VertexList[i].B = 0;
				VertexList[i].R = 1;
			}

		}
	}

}
