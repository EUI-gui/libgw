#include "GWImage.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // !STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifndef STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#endif // !STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif // !STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace GW;

GW::GWImage::GWImage() : m_width(0), m_height(0), m_channels(0), m_bits(nullptr), m_format(Bit_NULL)
{
}

GW::GWImage::GWImage(const std::string filename, Format format) : m_bits(nullptr), m_format(format)
{
	load(filename, format);
}

GW::GWImage::~GWImage()
{
	stbi_image_free(m_bits);
}

inline int GW::GWImage::width() const
{
	return m_width;
}

inline int GW::GWImage::height() const
{
	return m_height;
}

inline int GW::GWImage::channels() const
{
	return m_channels;
}

inline GWImage::Format GW::GWImage::getFormat() const
{
	return m_format;
}

unsigned char* GW::GWImage::bits()
{
	return m_bits;
}

const unsigned char* GW::GWImage::bits() const
{
	return m_bits;
}

bool GW::GWImage::load(const std::string filename, Format format)
{
	if (m_bits)
		stbi_image_free(m_bits);

	if (format == Bit8)
		m_bits = stbi_load(filename.c_str(), &m_width, &m_height, &m_channels, 0);
	else if (format == Bit16)
		m_bits = (unsigned char*)stbi_load_16(filename.c_str(), &m_width, &m_height, &m_channels, 0);
	else if (format == Bit32)
		m_bits = (unsigned char*)stbi_loadf(filename.c_str(), &m_width, &m_height, &m_channels, 0);
	else
		m_width = (0), m_height = (0), m_channels = (0), m_bits = (nullptr), m_format = (Bit_NULL);
	if (m_bits)
		return true;
	return false;
}

bool GW::GWImage::save(std::string filename, saveType type)
{
	bool bRet = false;
	if (type == PNG)
		bRet = stbi_write_png(filename.c_str(), m_width, m_height, m_channels, m_bits, m_width * m_channels * m_format);
	else if (type == JPG)
		bRet = stbi_write_jpg(filename.c_str(), m_width, m_height, m_channels, m_bits, 0);
	else if (type == BMP)
		bRet = stbi_write_bmp(filename.c_str(), m_width, m_height, m_channels, m_bits);
	else if (type == TGA)
		bRet = stbi_write_tga(filename.c_str(), m_width, m_height, m_channels, m_bits);
	else if (type == HDR)
		if(m_format == Bit32)
			bRet = stbi_write_hdr(filename.c_str(), m_width, m_height, m_channels, (float*)m_bits);
	return bRet;
}

bool GW::GWImage::resize(int width, int height)
{
	bool bRet = false;
	unsigned char* outBits = (unsigned char*)malloc(size_t(width)* height* m_channels * int(m_format));

	bRet = stbir_resize(m_bits, m_width, m_height, 0,
		outBits, width, height, 0,
		stbir_datatype(m_format), m_channels,
		STBIR_ALPHA_CHANNEL_NONE, 0,
		STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP,
		STBIR_FILTER_BOX, STBIR_FILTER_BOX,
		STBIR_COLORSPACE_SRGB, nullptr);
	if (bRet)
	{
		m_bits = outBits;
		return true;
	}
	else
	{
		free(outBits);
		return false;
	}
}

GWImage& GW::GWImage::operator=(const GWImage& image)
{
	memcpy(this, &image, sizeof(GWImage));
	m_bits = (unsigned char*)malloc(size_t(m_width)*m_height*m_channels * int(m_format));
	memcpy(this->m_bits, image.bits(), m_width * m_height * m_channels * int(m_format));
	return *this;
}
