xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 36;
 -1.92464;-0.01253;-1.93349;,
 0.00885;-0.01253;-2.73436;,
 0.00885;-25.88969;-1.30076;,
 -0.91092;-25.88969;-0.91978;,
 1.94234;-0.01253;-1.93349;,
 0.92863;-25.88969;-0.91978;,
 2.74322;-0.01253;0.00001;,
 1.30961;-25.88969;-0.00000;,
 1.94234;-0.01253;1.93350;,
 0.92863;-25.88969;0.91978;,
 0.00885;-0.01253;2.73438;,
 0.00885;-25.88969;1.30076;,
 -1.92464;-0.01253;1.93350;,
 -0.91092;-25.88969;0.91978;,
 -2.72552;-0.01253;0.00001;,
 -1.29190;-25.88969;0.00000;,
 -1.92464;-0.01253;-1.93349;,
 -0.91092;-25.88969;-0.91978;,
 0.00885;-0.01253;-2.73436;,
 -1.92464;-0.01253;-1.93349;,
 0.00885;2.45972;0.00001;,
 1.94234;-0.01253;-1.93349;,
 2.74322;-0.01253;0.00001;,
 1.94234;-0.01253;1.93350;,
 0.00885;-0.01253;2.73438;,
 -1.92464;-0.01253;1.93350;,
 -2.72552;-0.01253;0.00001;,
 -0.91092;-25.88969;-0.91978;,
 0.00885;-25.88969;-1.30076;,
 0.00885;-26.88701;-0.00000;,
 0.92863;-25.88969;-0.91978;,
 1.30961;-25.88969;-0.00000;,
 0.92863;-25.88969;0.91978;,
 0.00885;-25.88969;1.30076;,
 -0.91092;-25.88969;0.91978;,
 -1.29190;-25.88969;0.00000;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,19,20;,
 3;21,18,20;,
 3;22,21,20;,
 3;23,22,20;,
 3;24,23,20;,
 3;25,24,20;,
 3;26,25,20;,
 3;19,26,20;,
 3;27,28,29;,
 3;28,30,29;,
 3;30,31,29;,
 3;31,32,29;,
 3;32,33,29;,
 3;33,34,29;,
 3;34,35,29;,
 3;35,27,29;;
 
 MeshMaterialList {
  1;
  24;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\witch.jpg";
   }
  }
 }
 MeshNormals {
  19;
  -0.651246;0.389559;-0.651247;,
  -0.000001;0.389558;-0.921002;,
  0.651246;0.389559;-0.651247;,
  0.921002;0.389558;0.000001;,
  0.651247;0.389558;0.651247;,
  -0.000001;0.389558;0.921002;,
  -0.651247;0.389558;0.651246;,
  -0.921002;0.389558;0.000001;,
  -0.621535;-0.476854;-0.621534;,
  -0.000001;-0.476854;-0.878983;,
  0.621534;-0.476855;-0.621534;,
  0.878983;-0.476854;0.000000;,
  0.621534;-0.476855;0.621534;,
  -0.000001;-0.476854;0.878982;,
  -0.621536;-0.476854;0.621534;,
  -0.878983;-0.476852;0.000000;,
  0.380882;0.842530;-0.380882;,
  -0.000002;-1.000000;0.000000;,
  -0.380882;0.842530;0.380882;;
  24;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  3;1,0,16;,
  3;2,1,16;,
  3;3,2,16;,
  3;4,3,16;,
  3;5,4,18;,
  3;6,5,18;,
  3;7,6,18;,
  3;0,7,18;,
  3;8,9,17;,
  3;9,10,17;,
  3;10,11,17;,
  3;11,12,17;,
  3;12,13,17;,
  3;13,14,17;,
  3;14,15,17;,
  3;15,8,17;;
 }
 MeshTextureCoords {
  36;
  0.890720;0.461740;,
  0.894660;0.461740;,
  0.894660;0.414410;,
  0.890720;0.414410;,
  0.898590;0.461740;,
  0.898590;0.414410;,
  0.902520;0.461740;,
  0.902520;0.414410;,
  0.906460;0.461740;,
  0.906460;0.414410;,
  0.910390;0.461740;,
  0.910390;0.414410;,
  0.914320;0.461740;,
  0.914320;0.414410;,
  0.918260;0.461740;,
  0.918260;0.414410;,
  0.922190;0.461740;,
  0.922190;0.414410;,
  0.593570;0.611500;,
  0.612700;0.603580;,
  0.593570;0.585530;,
  0.574440;0.603580;,
  0.566520;0.584450;,
  0.574440;0.565320;,
  0.593570;0.557400;,
  0.612700;0.565320;,
  0.620620;0.584450;,
  0.986060;0.592170;,
  0.965340;0.583590;,
  0.965340;0.614060;,
  0.944630;0.592170;,
  0.936040;0.612880;,
  0.944630;0.633600;,
  0.965340;0.642180;,
  0.986060;0.633600;,
  0.994630;0.612880;;
 }
}
