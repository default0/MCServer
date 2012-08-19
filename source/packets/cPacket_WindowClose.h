
#pragma once

#include "cPacket.h"





class cPacket_WindowClose : public cPacket
{
public:
	cPacket_WindowClose()
		: m_WindowID( 0 )
	{
		m_PacketID = E_WINDOW_CLOSE;
	}
	
	virtual cPacket* Clone() const { return new cPacket_WindowClose(*this); }

	virtual int  Parse(cByteBuffer & a_Buffer) override;
	virtual void Serialize(AString & a_Data) const override;

	char m_WindowID;
};




