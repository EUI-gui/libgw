#pragma once


#include <iostream>

namespace GW
{
	class GWImage
	{
		enum Format {Bit8 = 1, Bit16 = 2, Bit32 = 4, Bit_NULL = 0 };
		enum saveType { PNG, JPG, BMP, TGA, HDR };

	public:
		GWImage();
		GWImage(const std::string filename, Format format = Bit8);
		~GWImage();
	public:
		inline int width() const;
		inline int height() const;
		inline int channels() const;
		inline Format getFormat() const;
	public:
		unsigned char* bits();
		const unsigned char* bits() const;

		bool load(const std::string filename, Format format = Bit8);
		bool save(std::string filename, saveType type = PNG);
		bool resize(int width, int height);

	protected:
		GWImage& operator=(const GWImage& image);
	private:
		int m_width;
		int m_height;
		int m_channels;
		Format m_format;
		unsigned char* m_bits;
	};
}


