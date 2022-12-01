#include "MathUtility.h"

namespace Color {

	Vector4 ToVectorColor(unsigned int color)
	{
		Vector4 result = {
			static_cast<float>((color >> 24) & 0xFF) / 255.0f,	// Red
			static_cast<float>((color >> 16) & 0xFF) / 255.0f,	// Green
			static_cast<float>((color >> 8) & 0xFF) / 255.0f,	// Blue
			static_cast<float>(color & 0xFF) / 255.0f };		// Alpha

		static auto toLinear = [](float color) {
			if (0 <= color && color <= 0.04045f) {

			}

		}


		return result;
	}

	unsigned int ToColorCode(const Vector4& color){
		return 0;
	}

	unsigned int HsvaToRgba(unsigned int h, unsigned int s, unsigned int v, unsigned int a) {
		float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;

		float H = fmodf(h, 360.0f);
		float V = fmodf(v, 256.0f);
		float S = fmodf(s, 256.0f);
		if (S <= 0) {
			r = v;
			g = v;
			b = v;
		}
		else {

			int Hi = (int)(H / 60.0f);
			float F = H / 60.0f - (float)Hi;
			float M = V * (1.0f - S / 255.0f);
			float N = V * (1.0f - S / 255.0f * F);
			float K = V * (1.0f - S / 255.0f * (1.0f - F));

			switch (Hi)
			{
			case 0:
				r = V;
				g = K;
				b = M;
				break;
			case 1:
				r = N;
				g = V;
				b = M;
				break;
			case 2:
				r = M;
				g = V;
				b = K;
				break;
			case 3:
				r = M;
				g = N;
				b = V;
				break;
			case 4:
				r = K;
				g = M;
				b = V;
				break;
			case 5:
			default:
				r = V;
				g = M;
				b = N;
				break;
			}
		}
		unsigned int red = (unsigned int)r;
		unsigned int green = (unsigned int)g;
		unsigned int blue = (unsigned int)b;
		return red << 24 | green << 16 | blue << 8 | alpha;
	}
}