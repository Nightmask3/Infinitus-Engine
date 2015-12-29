#include "PhysicsManager.h"

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::Update()
{
	// Three Stages
	// Simulation : Update the physics variables of all objects that have physics components (Apply gravity, velocity, forces etc.)
	Simulation();
	// Collision Detection : Checking every Physics Component that has a Rigid Body for collision against every other rigid body
	DetectCollision();
	// Resolution: Apply the physics values to the game object transforms
	Resolution();
}
void PhysicsManager::Simulation()
{
	PhysicsComponent * pSimulation = nullptr;
	while (frameManager.frametime > 0.0)
	{
		float deltatime = std::min(frameManager.frametime, frameManager.dt);
		for (auto iterator = PhysicsObjectsList.begin(); iterator != PhysicsObjectsList.end(); ++iterator)
		{
			// Compute the change to the physics components of all objects, except those which are non - moving
			pSimulation = static_cast<PhysicsComponent *>(*iterator);
			if (pSimulation->mMass == 0.0f)
				continue;
			pSimulation->Integrate(frameManager.t, deltatime);
		}
		frameManager.frametime -= deltatime;
		frameManager.t += deltatime;
	}
	
}
void PhysicsManager::DetectCollision()
{
	PhysicsComponent * pCollisionDet1 = nullptr, *pCollisionDet2 = nullptr;
	for (auto iterator1 = PhysicsObjectsList.begin(); iterator1 != PhysicsObjectsList.end(); ++iterator1)
	{
		pCollisionDet1 = static_cast<PhysicsComponent *>(*iterator1);
		for (auto iterator2 = iterator1 + 1; iterator2 != PhysicsObjectsList.end(); ++iterator2)
		{
			pCollisionDet2 = static_cast<PhysicsComponent *>(*iterator2);
			IntersectData data = pCollisionDet1->GetCollider().Intersect(pCollisionDet2->GetCollider());
			if (data.GetDoesIntersect())
			{
				if (pCollisionDet1->mpShape->mType == Bounding::AABB && pCollisionDet2->mpShape->mType == Bounding::SPHERE)
				{
					// If Spheres intersect with walls they should return to their last position
					float Penetration = 0.0f;
					BoundingSphere * sphere = static_cast<BoundingSphere *>(pCollisionDet2->mpShape);
					if (data.GetDirection() == IntersectData::LEFT || data.GetDirection() == IntersectData::RIGHT)
					{
						Penetration = sphere->GetRadius() - abs(data.GetDifference().x);
						// If Left collision, trying to move towards negative X direction, hence add
						if (data.GetDirection() == IntersectData::RIGHT)
						{
							pCollisionDet2->mPositionCurr.x += Penetration;
						}
						// And vice versa
						else
						{
							pCollisionDet2->mPositionCurr.x -= Penetration;
						}
					}
					else if (data.GetDirection() == IntersectData::UP || data.GetDirection() == IntersectData::DOWN)
					{
						Penetration = sphere->GetRadius() - abs(data.GetDifference().y);
						// If Up collision, trying to move towards negative Y direction, hence add
						if (data.GetDirection() == IntersectData::UP)
						{
							pCollisionDet2->mPositionCurr.y += Penetration;
						}
						// And vice versa
						else
						{
							pCollisionDet2->mPositionCurr.y -= Penetration;
						}
					}
					else if (data.GetDirection() == IntersectData::FRONT || data.GetDirection() == IntersectData::BACK)
					{
						Penetration = sphere->GetRadius() - abs(data.GetDifference().z);
						// If Front collision, trying to move towards negative Z direction, hence add
						if (data.GetDirection() == IntersectData::FRONT)
						{
							pCollisionDet2->mPositionCurr.z += Penetration;
						}
						// And vice versa
						else
						{
							pCollisionDet2->mPositionCurr.z -= Penetration;
						}
					}
					// Creates collision event
					CollideEvent collideEvent;
					collideEvent.mpObject1 = pCollisionDet1->mOwner;
					collideEvent.mpObject2 = pCollisionDet2->mOwner;
					// Makes the collided bodies handle it
					collideEvent.mpObject1->HandleEvent(&collideEvent);
					//collideEvent.mpObject2->HandleEvent(&collideEvent);
				}
				else if (pCollisionDet1->mpShape->mType == Bounding::SPHERE && pCollisionDet2->mpShape->mType == Bounding::PLANE)
				{
					// If Spheres intersect with ground plane they should return to their last position, and no more acceleration or velocity along the Y axis
					//pCollisionDet1->mPositionCurr.y = pCollisionDet1->mPositionPrev.y;
					pCollisionDet1->mVelocity.y = 0;
					pCollisionDet1->mAcceleration = false;
					//// Creates collision event
					//CollideEvent collideEvent;
					//collideEvent.mpObject1 = pCollisionDet1->mOwner;
					//collideEvent.mpObject2 = pCollisionDet2->mOwner;
					//// Makes the collided bodies handle it
					//collideEvent.mpObject1->HandleEvent(&collideEvent);
					//collideEvent.mpObject2->HandleEvent(&collideEvent);
				}
				else if (pCollisionDet1->mpShape->mType == Bounding::SPHERE && pCollisionDet2->mpShape->mType == Bounding::SPHERE && (pCollisionDet1->mIsPlayer == true || pCollisionDet2->mIsPlayer == true))
				{
					// If Spheres intersect with another sphere, AND ONE OF THE SPHERES ARE THE PLAYER
					pCollisionDet1->mPositionCurr.x = 1;
					pCollisionDet1->mPositionCurr.z = 1;
					pCollisionDet1->mLifeCount--;
					pCollisionDet2->mLifeCount--;
					if (pCollisionDet1->mLifeCount == 0 || pCollisionDet2->mLifeCount == 0)
						mGameOver = true;
					//// Creates collision event
					//CollideEvent collideEvent;
					//collideEvent.mpObject1 = pCollisionDet1->mOwner;
					//collideEvent.mpObject2 = pCollisionDet2->mOwner;
					//// Makes the collided bodies handle it
					//collideEvent.mpObject1->HandleEvent(&collideEvent);
					//collideEvent.mpObject2->HandleEvent(&collideEvent);
				}
				
			}
			// Set bounding box color back to blue
			else 
			{
				for (int i = 0; i < pCollisionDet1->VertexList.size(); i++)
				{
					pCollisionDet1->VertexList[i].B = 1;
					pCollisionDet1->VertexList[i].R = 0;
				}
				pCollisionDet1->mAcceleration = true;
			}
		}
	}
}

void PhysicsManager::Resolution()
{
	PhysicsComponent * pSimulation = nullptr;
	for (auto iterator = PhysicsObjectsList.begin(); iterator != PhysicsObjectsList.end(); ++iterator)
	{
		pSimulation = static_cast<PhysicsComponent *>(*iterator);
		pSimulation->UpdateTransform();
	}
}

void PhysicsManager::SetBoundingBoxType(Bounding::RigidBodyType type)
{
	PhysicsComponent * p = nullptr;
	TransformComponent * t = nullptr;
	SpriteComponent * s = nullptr;
	VertexCollider temp;
	if (type == Bounding::SPHERE)
	{
		p = static_cast<PhysicsComponent *>(PhysicsObjectsList.back());
		t = static_cast<TransformComponent *>(PhysicsObjectsList.back()->mOwner->GetComponent(Component::TRANSFORM));
		s = static_cast<SpriteComponent *>(PhysicsObjectsList.back()->mOwner->GetComponent(Component::SPRITE));
		Vector3D center;
		Vector3DSet(&center, t->mTranslation.m[0][3] + t->mScale.m[0][0], t->mTranslation.m[1][3] + t->mScale.m[1][1], t->mTranslation.m[2][3] + t->mScale.m[2][2], 1);
		p->mpShape = new BoundingSphere(center);
		p->mpShape->mOwner = p;
		// Sets values of collider bounding box
		for (int i = 0; i < s->GetVertexList().size(); i++)
		{
			temp.X = s->GetVertexList()[i].X;
			temp.Y = s->GetVertexList()[i].Y;
			temp.Z = s->GetVertexList()[i].Z;
			// All debug bounding shapes are green by default (assumes that they are not colliding in first frame)
			temp.R = 0;
			temp.G = 0;
			temp.B = 1;
			temp.A = 0.5;
			temp.U = 0;
			temp.V = 0;
			p->VertexList.push_back(temp);
		}
		for (int i = 0; i < s->GetIndexList().size(); i++)
		{
			unsigned int temp = s->GetIndexList()[i];
			p->IndexList.push_back(temp);
		}
	}
	else if (type == Bounding::AABB)
	{
		p = static_cast<PhysicsComponent *>(PhysicsObjectsList.back());
		t = static_cast<TransformComponent *>(PhysicsObjectsList.back()->mOwner->GetComponent(Component::TRANSFORM));
		s = static_cast<SpriteComponent *>(PhysicsObjectsList.back()->mOwner->GetComponent(Component::SPRITE));
		Vector3D min, max;
		// Begin returns an iterator, Back returns an object 
		Vector3DSet(&min, s->GetVertexList().begin()->X, s->GetVertexList().begin()->Y, s->GetVertexList().begin()->Z, 1);
		Vector3DSet(&max, s->GetVertexList().back().X, s->GetVertexList().back().Y, s->GetVertexList().back().Z, 1);
		Vector3D center;
		Vector3DSet(&center, t->mTranslation.m[0][3], t->mTranslation.m[1][3], t->mTranslation.m[2][3], 1);
		p->mpShape = new BoundingBox(min, max);
		p->mpShape->mOwner = p;
		BoundingBox * b;
		b = static_cast<BoundingBox *>(p->mpShape);
		b->SetCenter(center);
		// Sets values of collider bounding box
		for (int i = 0; i < s->GetVertexList().size(); i++)
		{
			temp.X = s->GetVertexList()[i].X;
			temp.Y = s->GetVertexList()[i].Y;
			temp.Z = s->GetVertexList()[i].Z;
			// All debug bounding shapes are blue by default (assumes that they are not colliding in first frame)
			temp.R = 0;
			temp.G = 0;
			temp.B = 1;
			temp.A = 0.5;
			temp.U = 0;
			temp.V = 0;
			p->VertexList.push_back(temp);
		}
	}
	else if (type == Bounding::PLANE)
	{
		p = static_cast<PhysicsComponent *>(PhysicsObjectsList.back());
		p->mpShape = new Plane(Vector3D(0, 1, 0, 0), -0.5); // Sets the origin plane as tile top
	}
}
