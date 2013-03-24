//
//  ofxGiantImage.cpp
//
//  Created by Tim Knapen on 15/03/13.
//  www.timknapen.be
//

#include "ofxGiantImage.h"


//--------------------------------------------------------
ofxGiantImage::ofxGiantImage(){
    wtiles = htiles = width = height = 0;
    tileSize = 512; // ofImage uses more than the imagesize for the openGL texture, so maybe I should stay a bit under the ideal?
}

//--------------------------------------------------------
ofxGiantImage::~ofxGiantImage(){
    wtiles = htiles = 0;
    for (int i = 0; i < tiles.size(); i++) {
        tiles[i]->clear();
        delete tiles[i];
    }
    tiles.clear();
}

//--------------------------------------------------------
void ofxGiantImage::loadImage(string filePath){
    
    // ofImage does a weird hack for the edges of openGL textures switch that off
    ofDisableTextureEdgeHack();

    
    // load into a big image
    ofImage * img = new ofImage();
    img->setUseTexture(false);
    if(!img->loadImage(filePath)){
        cout << "I couldn't load the image from path: "<<filePath<<endl;
        return;
    }
    if(!img->type == OF_IMAGE_COLOR){
        cout << "WARNING the ofxTile can only display 3 channel color images now! "<<endl;
        return;
    }
    
    width = img->width;
    height = img->height;
    cout << "Loaded source image of "<<width<<" by "<<height<<" pixels"<<endl;
    wtiles = (int) ceilf(width/(float)tileSize);
    htiles = (int) ceilf(height/(float)tileSize);
    
    // in the special and stupid case that you load a source image that is smaller than the size of a tile just use the source image.
    if( width < tileSize ||  height < tileSize){
        unsigned char * imgpix = img->getPixels();
        unsigned char tilepix[3*img->width*img->height];
        ofTexture * tile = new ofTexture();
        tile->allocate(img->width, img->height, GL_RGB);
        tile->loadData(tilepix, img->width, img->height, GL_RGB);
        tiles.push_back(tile);
        img->clear();
        delete img;
        ofEnableTextureEdgeHack();
        return;
    }
    
    unsigned char * imgpix = img->getPixels();
	unsigned char tilepix[3*tileSize*tileSize];
    
    // now start making tiles!
    for(int y = 0; y < htiles; y++){
        for (int x = 0; x < wtiles; x++) {
            
            int x1 = tileSize * x;
            int y1 = tileSize * y;
            //x1 = MIN(width - tileSize, x1);     // HACK -- this way the tiles on the far right edge stay within the bounds..
            //y1 = MIN(height - tileSize, y1);    // HACK
            int tileWidth = MIN(tileSize, width - x1); // only necessary for the tiles on the far right
            int tileHeight = MIN(tileSize, height - y1); // only necessary for the tiles on the bottom row
            ofTexture * tile = new ofTexture();
			
			tile->allocate(tileWidth, tileHeight, GL_RGB);
            
            // copy pixels into tilepix row by row
            for (int iy = 0; iy < tileHeight; iy++) {
                memcpy(&(tilepix[3 * (iy * tileWidth)]),
                       &(imgpix[3 * ( x1 + (y1+iy)*img->width)]),
                       3 * tileSize * sizeof(unsigned char));
            }
            
			tile->loadData(tilepix, tileWidth, tileHeight, GL_RGB);
            tiles.push_back(tile);
                        
        }
    }
    
    if( wtiles * htiles != tiles.size()){
        cout << "WARNING the tiler created a grid of "<<(wtiles*htiles)<<" tiles but the vector has "<<tiles.size()<<" tiles!"<<endl;
    }else{
        cout << "the tiler created "<< wtiles <<" by "<<htiles<<" tiles ( = "<< (wtiles * htiles) <<" )"<<endl;
    }
    
    // destroy the source image
    img->clear();
    delete img;
    
    // switch the ofImage texture hack back on
    ofEnableTextureEdgeHack();

}

//------------------------------------------------
void ofxGiantImage::draw(float x, float y, float w, float h){
    
    int x0 = floorf(x/(float)tileSize);
    int y0 = floorf(y/(float)tileSize);
    x0 = MAX(0, x0);
    y0 = MAX(0, y0);
    int maxix = ceilf( (x + w) / (float) tileSize );
    int maxiy = ceilf( (y + h) / (float) tileSize );
    maxix = MIN( wtiles, maxix);
    maxiy = MIN( htiles, maxiy);
    
    ofPushMatrix();
    ofTranslate( - x,  -y);
    //ofScale(ofGetWidth()/width, ofGetWidth()/width);
    for(int ix = x0 ; ix < maxix; ix ++ ){
        for(int iy = y0 ; iy < maxiy; iy++){
            tiles[ ix + (iy * wtiles)]->draw( ix * tileSize, iy * tileSize);
        }
    }
    ofPopMatrix();
}

//------------------------------------------------
void ofxGiantImage::drawBounds(float x, float y, float w, float h){
    ofPushStyle();
    ofEnableAlphaBlending();
    //ofSetColor(0, 0, 0, 10);
    ofSetLineWidth(3);
    ofNoFill();
    
    int x0 = floorf(x/(float)tileSize);
    int y0 = floorf(y/(float)tileSize);
    x0 = MAX(0, x0);
    y0 = MAX(0, y0);
    int maxix = ceilf( (x + w) / (float) tileSize );
    int maxiy = ceilf( (y + h) / (float) tileSize );
    maxix = MIN( wtiles, maxix);
    maxiy = MIN( htiles, maxiy);
	ofTexture * tile;

    ofPushMatrix();
    ofTranslate( - x,  -y);
    for(int ix = x0 ; ix < maxix; ix ++ ){
        for(int iy = y0 ; iy < maxiy; iy++){
			tile = tiles[ ix + (iy * wtiles)];
            ofPushMatrix();
            ofTranslate(ix * tileSize, iy * tileSize);
            ofRect(0, 0,  tile->getWidth(),tile->getHeight());
            

            ofPopMatrix();
        }
    }
    ofPopMatrix();
    
    


    ofPushMatrix();
	
	ofSetLineWidth(1);
    ofSetColor(100,100,100,70);
    ofTranslate(20, 20);
    ofScale(800/width, 800/width);
    for(int ix = 0 ; ix < wtiles; ix ++ ){
        for(int iy = 0 ; iy < htiles; iy++){
            ofRect(ix * tileSize, iy * tileSize,  tiles[ ix + (iy * wtiles)]->getWidth(), tiles[ ix + (iy * wtiles)]->getHeight());
        }
    }
    
    ofSetColor(0, 255, 0);

    for(int ix = x0 ; ix < maxix; ix ++ ){
        for(int iy = y0 ; iy < maxiy; iy++){
            
            ofRect(ix * tileSize, iy * tileSize,  tiles[ ix + (iy * wtiles)]->getWidth(), tiles[ ix + (iy * wtiles)]->getHeight());
        }
    }
    ofPopMatrix();
    ofDisableAlphaBlending();
    
    ofPopStyle();

}