/*
 * Copyright (c) 2011. Philipp Wagner <bytefish[at]gmx[dot]de>.
 * Released to public domain under terms of the BSD Simplified license.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the organization nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *   See <http://www.opensource.org/licenses/bsd-license>
 */

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <stdio.h>
#include <unistd.h>
#include "cloud.h"
#include "cloudTimer.h"
#include "clopencv.h"

using namespace cv;
using namespace std;

static Mat norm_0_255(InputArray _src) {
    Mat src = _src.getMat();
    // Create and return normalized image:
    Mat dst;
    switch(src.channels()) {
    case 1:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

int main(int argc, char **argv) {
  // These vectors hold the images and corresponding labels.
  vector<Mat> images;
  vector<int> labels;
  Ptr<FaceRecognizer> model = createEigenFaceRecognizer();

  Mat testSample;
  int testLabel;
  int height;
  auto begin = std::chrono::high_resolution_clock::now(); 
  auto end = std::chrono::high_resolution_clock::now(); 
  auto time_span= std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
  string output_folder = ".";
  TCPSocket socket;
  
  // Reading the arguments
    // Check for valid command line arguments, print usage
    // if no arguments were given.
    if (argc < 5) {
        cout << "usage: " << argv[0] << " <hostname> <port> <csv.ext> <output_folder> " << endl;
        exit(1);
    }
    char * hostname = argv[1];
    int portno = atoi(argv[2]);
    if (argc == 5) {

        output_folder = string(argv[4]);
    }
    // Get the path to your CSV.
    string fn_csv = string(argv[3]);
    cloudInit(portno, hostname, socket);
    // Read in the data. This can fail if no valid
    // input filename is given.
    begin = std::chrono::high_resolution_clock::now();
    try {
        read_csv(fn_csv, images, labels);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
    end = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
    std::cout << "Total reading time: " << time_span.count() << "sec" << std::endl;
    // Quit if there are not enough images for this demo.
    if(images.size() <= 1) {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(CV_StsError, error_message);
    }
    // Get the height from the first image. We'll need this
    // later in code to reshape the images to their original
    // size:
    height = images[0].rows;
    // The following lines simply get the last images from
    // your dataset and remove it from the vector. This is
    // done, so that the training data (which we learn the
    // cv::FaceRecognizer on) and the test data we test
    // the model with, do not overlap.
    testSample = images[images.size() - 1];
    testLabel = labels[labels.size() - 1];
    images.pop_back();
    labels.pop_back();
    // The following lines create an Eigenfaces model for
    // face recognition and train it with the images and
    // labels read from the given CSV file.
    // This here is a full PCA, if you just want to keep
    // 10 principal components (read Eigenfaces), then call
    // the factory method like this:
    //
    //      cv::createEigenFaceRecognizer(10);
    //
    // If you want to create a FaceRecognizer with a
    // confidence threshold (e.g. 123.0), call it with:
    //
    //      cv::createEigenFaceRecognizer(10, 123.0);
    //
    // If you want to use _all_ Eigenfaces and have a threshold,
    // then call the method like this:
    //
    //      cv::createEigenFaceRecognizer(0, 123.0);
    //
    begin = std::chrono::high_resolution_clock::now();
    
    int * c_labels;
    cloudMalloc(socket, (void **)&c_labels, labels.size() * sizeof(int));

    char *  c_images; 
    Mat imagesMat = model->asFaceRowMatrix(images, 0);
    cloudMalloc(socket, (void **)&c_images, imagesMat.total() * imagesMat.elemSize());
    
    double *  c_mean; 
    double *  d_mean; 
    cloudMalloc(socket, (void **)&c_mean, imagesMat.cols * sizeof(double));
    d_mean = (double *) malloc(imagesMat.cols * sizeof(double));
    
    double *  c_eigenValues; 
    double *  d_eigenValues; 
    cloudMalloc(socket, (void **)&c_eigenValues, imagesMat.rows * sizeof(double));
    d_eigenValues = (double *) malloc(imagesMat.rows * sizeof(double));

    double *  c_eigenVectors; 
    double *  d_eigenVectors; 
    cloudMalloc(socket, (void **)&c_eigenVectors, imagesMat.total() * sizeof(double));
    d_eigenVectors = (double *) malloc(imagesMat.total() * sizeof(double));
    
    double *  c_projections; 
    double *  d_projections; 
    cloudMalloc(socket, (void **)&c_projections, imagesMat.rows * imagesMat.rows * sizeof(double));
    d_projections = (double *) malloc(imagesMat.rows * imagesMat.rows * sizeof(double));
    
    CloudTimer cloudTimer;
    cloudTimer.start();
  
    cloudMemcpy(socket,  c_labels,  &labels[0],  labels.size() * sizeof(int), cloudMemcpyClientToCloud, NoCompression /*SnappyCompression*/);
    cloudMemcpy(socket,  c_images,  imagesMat.data,  imagesMat.total() * imagesMat.elemSize(), cloudMemcpyClientToCloud, NoCompression /*SnappyCompression*/);
    
    cloudFaceTrain(socket, imagesMat.rows, imagesMat.cols, c_images, c_labels, c_eigenValues, c_eigenVectors, c_mean, c_projections);
    

    cloudMemcpy(socket,  d_mean,  c_mean,  imagesMat.cols * sizeof(double), cloudMemcpyCloudToClient, NoCompression /*SnappyCompression*/);
    cloudMemcpy(socket,  d_eigenValues,  c_eigenValues,  imagesMat.rows * sizeof(double), cloudMemcpyCloudToClient, NoCompression /*SnappyCompression*/);
    cloudMemcpy(socket,  d_eigenVectors,  c_eigenVectors,  imagesMat.total() * sizeof(double), cloudMemcpyCloudToClient, NoCompression /*SnappyCompression*/);
    cloudMemcpy(socket,  d_projections,  c_projections,   imagesMat.rows * imagesMat.rows * sizeof(double), cloudMemcpyCloudToClient, NoCompression /*SnappyCompression*/);
    
    cloudTimer.end();    
    double time_in_seconds = cloudTimer.getDurationInSeconds();


    end = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
    std::cout << "Total reading time: " << time_span.count() << "sec" << std::endl;
    model->setMat("eigenvalues", Mat(imagesMat.rows, 1 , CV_64FC1, d_eigenValues));
    model->setMat("eigenvectors", Mat(imagesMat.cols, imagesMat.rows , CV_64FC1, d_eigenVectors));
    model->setMat("mean", Mat(1, imagesMat.cols , CV_64FC1, d_mean));
    vector<Mat> projectionsVec;
    for (int i = 0 ; i < imagesMat.rows; i++)
      projectionsVec.push_back(Mat(1, imagesMat.rows, CV_64FC1, reinterpret_cast<double *>(d_projections) +  i * imagesMat.rows));
    std::cout << projectionsVec[100] << std::endl;
    model->setMatVector("projections", projectionsVec);
    model->setMat("labels", ((InputArray)labels).getMat());

    // The following line predicts the label of a given
    // test image:
    int predictedLabel =  model->predict(testSample);
    //
    // To get the confidence of a prediction call the model with:
    //
    //      int predictedLabel = -1;
    //      double confidence = 0.0;
    //      model->predict(testSample, predictedLabel, confidence);
    //
    string result_message = format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);
    cout << result_message << endl;

    // Display or save:
    if(argc == 2) {
        imshow("mean", norm_0_255(mean.reshape(1, images[0].rows)));
    } else {
        imwrite(format("%s/mean.png", output_folder.c_str()), norm_0_255(mean.reshape(1, images[0].rows)));
    }
    end = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
    std::cout << "Total image writing time: " << time_span.count() << "sec" << std::endl;
    // Display or save the Eigenfaces:
    for (int i = 0; i < min(10, W.cols); i++) {
        string msg = format("Eigenvalue #%d = %.5f", i, eigenvalues.at<double>(i));
        cout << msg << endl;
        // get eigenvector #i
        Mat ev = W.col(i).clone();
        // Reshape to original size & normalize to [0...255] for imshow.
        Mat grayscale = norm_0_255(ev.reshape(1, height));
        // Show the image & apply a Jet colormap for better sensing.
        Mat cgrayscale;
        applyColorMap(grayscale, cgrayscale, COLORMAP_JET);
        // Display or save:
        if(argc == 2) {
            imshow(format("eigenface_%d", i), cgrayscale);
        } else {
            imwrite(format("%s/eigenface_%d.png", output_folder.c_str(), i), norm_0_255(cgrayscale));
        }
    }

    // Display or save the image reconstruction at some predefined steps:
    for(int num_components = min(W.cols, 10); num_components < min(W.cols, 300); num_components+=15) {
        // slice the eigenvectors from the model
        Mat evs = Mat(W, Range::all(), Range(0, num_components));
        Mat projection = subspaceProject(evs, mean, images[0].reshape(1,1));
        Mat reconstruction = subspaceReconstruct(evs, mean, projection);
        // Normalize the result:
        reconstruction = norm_0_255(reconstruction.reshape(1, images[0].rows));
        // Display or save:
        if(argc == 2) {
            imshow(format("eigenface_reconstruction_%d", num_components), reconstruction);
        } else {
            imwrite(format("%s/eigenface_reconstruction_%d.png", output_folder.c_str(), num_components), reconstruction);
        }
    }
    // Display if we are not writing to an output folder:
    if(argc == 2) {
        waitKey(0);
    }
  cloudFinish(socket);
  return 0;
}
