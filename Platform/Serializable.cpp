/*
 Copyright (c) 2008 TrueCrypt Foundation. All rights reserved.

 Governed by the TrueCrypt License 2.8 the full text of which is contained
 in the file License.txt included in TrueCrypt binary and source code
 distribution packages.
*/

#include "Serializable.h"
#include "SerializerFactory.h"

namespace TrueCrypt
{
	string Serializable::DeserializeHeader (shared_ptr <Stream> stream)
	{
		Serializer sr (stream);
		return sr.DeserializeString ("SerializableName");
	}

	Serializable *Serializable::DeserializeNew (shared_ptr <Stream> stream)
	{
		string name = Serializable::DeserializeHeader (stream);
		Serializable *serializable = SerializerFactory::GetNewSerializable (name);
		serializable->Deserialize (stream);

		return serializable;
	}

	void Serializable::Serialize (shared_ptr <Stream> stream) const
	{
		Serializer sr (stream);
		Serializable::SerializeHeader (sr, SerializerFactory::GetName (typeid (*this)));
	}

	void Serializable::SerializeHeader (Serializer &serializer, const string &name)
	{
		serializer.Serialize ("SerializableName", name);
	}
}
