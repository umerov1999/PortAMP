#pragma once

#include <vector>

#include "Decoders/iWaveDataProvider.h"

class clBlob;
struct sFLACStreamData;

/// FLAC decoder
class clFLACDataProvider: public iWaveDataProvider
{
public:
	explicit clFLACDataProvider( const std::shared_ptr<clBlob>& Data );
	virtual ~clFLACDataProvider();

	virtual const sWaveDataFormat& GetWaveDataFormat() const override { return m_Format; }

	virtual const uint8_t* GetWaveData() const override;
	virtual size_t GetWaveDataSize() const override;

	virtual size_t StreamWaveData( size_t Size ) override;
	virtual bool IsStreaming() const { return true; }
	virtual bool IsEndOfStream() const { return m_IsEndOfStream; }
	virtual void Seek( float Seconds ) override;

private:
	int DecodeFromFile( size_t Size );

private:
	std::shared_ptr<clBlob> m_Data;
	sWaveDataFormat m_Format;

	std::vector<uint8_t> m_DecodingBuffer;
	size_t m_BufferUsed;

	bool m_IsEndOfStream;

	std::shared_ptr<sFLACStreamData> m_StreamData;
};
