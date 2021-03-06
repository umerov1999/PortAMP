#pragma once

#include <memory>
#include <vector>

#include "Decoders/iWaveDataProvider.h"

class clBlob;

struct OggOpusFile;

/// Opus decoder
class clOpusDataProvider: public iWaveDataProvider
{
public:
	explicit clOpusDataProvider( const std::shared_ptr<clBlob>& Data );
	virtual ~clOpusDataProvider();

	virtual const sWaveDataFormat& GetWaveDataFormat() const override { return m_Format; }

	virtual const uint8_t* GetWaveData() const override;
	virtual size_t GetWaveDataSize() const override;

	virtual size_t StreamWaveData( size_t Size ) override;
	virtual bool IsStreaming() const override { return true; }
	virtual bool IsEndOfStream() const override { return m_IsEndOfStream; }
	virtual void Seek( float Seconds ) override;

private:
	int DecodeFromFile( size_t Size, size_t BytesRead );

private:
	std::shared_ptr<clBlob> m_Data;
	sWaveDataFormat m_Format;

	std::vector<uint8_t> m_DecodingBuffer;
	size_t m_BufferUsed;

	bool m_IsEndOfStream;

	// Opus stuff
	OggOpusFile* m_OpusFile;
};
