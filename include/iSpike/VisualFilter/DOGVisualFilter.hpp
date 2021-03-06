#ifndef DOGVISUALFILTER_HPP_
#define DOGVISUALFILTER_HPP_

#include <iSpike/VisualDataReducer/LogPolarVisualDataReducer.hpp>
#include <iSpike/Bitmap.hpp>

namespace ispike {

	/** This class represents a Difference Of Gaussians filter */
	class DOGVisualFilter {
		public:
			DOGVisualFilter(LogPolarVisualDataReducer* reducer);
			~DOGVisualFilter();
			Bitmap& getBitmap();
			bool isInitialized(){ return initialized; }
			void setPositiveSigma(double positiveSigma) { this->positiveSigma = positiveSigma; }
			void setNegativeSigma(double negativeSigma) { this->negativeSigma = negativeSigma; }
			void setPositiveFactor(double positiveFactor) { this->positiveFactor = positiveFactor; }
			void setNegativeFactor(double negativeFactor) { this->negativeFactor = negativeFactor; }
			void setOpponencyTypeID(int opponencyTypeID);
			void update();

		private:
			//==========================  VARIABLES  =======================
			LogPolarVisualDataReducer* reducer;

			/** Sigma for Gaussian blurring of positive images */
			double positiveSigma;

			/** Sigma for Gaussian blurring of negative images */
			double negativeSigma;

			/** Factor by which positive image is multiplied during subtraction */
			double positiveFactor;

			/** Factor by which positive image is multiplied during subtraction */
			double negativeFactor;

			/** ID controlling the type of opponency map that is generated */
			int opponencyTypeID;

			/** Controls whether the final image is normalized or not */
			bool normalize;

			/** Records when class has been initialized */
			bool initialized;

			/** Final output bitmap */
			Bitmap* outputBitmap;

			/** Red visual data */
			Bitmap* redBitmap;

			/** Green visual data */
			Bitmap* greenBitmap;

			/** Blue visual data */
			Bitmap* blueBitmap;

			/** Yellow visual data */
			Bitmap* yellowBitmap;

			/** Black and white visual data - 2 maps are used for this and swapped around */
			Bitmap* greyBitmap1;

			/** Second map for black and white visual data */
			Bitmap* greyBitmap2;

			/** Controls which grey bitmap data is read into */
			bool useGreyBitmap1;

			/** Positive blurred bitmap */
			Bitmap* positiveBlurredBitmap;

			/** Negative blurred bitmap */
			Bitmap* negativeBlurredBitmap;


			//==========================  METHODS  =========================
			void calculateLogDifference(Bitmap& bitmap1, Bitmap& bitmap2);
			void calculateOpponency(Bitmap& bitmap1, Bitmap& bitmap2);
			void extractRedChannel(Bitmap& inputImage);
			void extractGreenChannel(Bitmap& inputImage);
			void extractBlueChannel(Bitmap& inputImage);
			void extractYellowChannel();
			void extractGreyChannel(Bitmap& inputBitmap, Bitmap& newBitmap, bool logInput);
			void gaussianBlur(Bitmap& inputBitmap, Bitmap& resultBitmap, double sigma);
			void initialize(int width, int height);
			void normalizeImage(Bitmap& image);
			void subtractImages(Bitmap& firstImage, Bitmap& secondImage, Bitmap& result);
			void subtractImages(Bitmap& firstImage, Bitmap& secondImage, double positiveFactor, double negativeFactor, Bitmap& result);
	};

}

#endif /* DOGVISUALFILTER_HPP_ */
