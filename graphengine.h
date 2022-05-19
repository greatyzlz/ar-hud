#ifndef GRAPHEGINE_H
#define GRAPHEGINE_H
#ifdef __cplusplus
extern "C"{
#endif


#include <wchar.h>
#define VERSION "version 1.11"
typedef struct
{
    int x;
    int y;
    int z;
}sPoint3;

typedef struct
{
    float x;
    float y;
    float z;
}sPoint3f;

typedef struct
{
    float x;
    float y;
}sPoint2f;

typedef struct
{
    unsigned int width;
    unsigned int height;
}sRectSize;

typedef struct
{
    float red;
    float green;
    float blue;
    float alpha;
}sColor;

typedef struct
{
    float red;
    float green;
    float blue;
}sColorRGB;

typedef struct
{
    sPoint3f Position; // Light position in eye coords.
    sColorRGB AmbientLightColor; // Ambient light color
    sColorRGB DiffuseLightColor; // Ambient light color
    sColorRGB SpecularLightColor; // Ambient light color
}sLightInfo;

typedef struct
{
    float AmbientReflectivity;// Ambient reflectivity intensity : default 0.1
    float DiffuseReflectivity;// Diffuse reflectivity intensity : default 50.0
    float SpecularReflectivity;// Specular reflectivity intensity : default 15.0
    float Shininess;// Specular shininess factor : default 5.0
}sMaterialInfo;

typedef struct
{
    sPoint3f Position; // Camera position in world space
    sPoint3f Focus;    // The point that the camera is looking at
    int Up;    // Camare's up direction, 1 is up, -1 is upside-down
    float FoV; //Camera's view angle
    float Ratio; //the width and height ratio of the view area
    float Near; //view frustum near
    float Far;  // view frustum far
}sCameraInfo;

typedef enum
{
    HIDE=0,
    SHOW
}eShowStatus;

typedef enum
{
    MASK_EMPTY=0,
    MASK_RIGHT_TO_LEFT,
    MASK_WINDOW_SHADES,
    MASK_MIDDLE_TO_SIDE,
    MASK_MOSAIC,
    MASK_SIDE_TO_MIDDLE,
    MASK_LEFT_TO_RIGHT
}eMaskEffect;

typedef enum
{
    BLEND_EMPTY=0,
    BLEND_FRAGMENTWINDOW_BLACK,
    BLEND_FRAGMENTWINDOW_WHITE,
    BLEND_TEXT_DANGER
}eBlendEffect;

typedef enum
{
    BRUSH_TOOL=1,
    HMI
}eStatePattern;

//morph effect
typedef enum
{
    NONE_STRATEGY=0,
    NORMAL_STRATEGY,
    GENIEEFFECT_STRATEGY,
    WAVEEFFECT_STRATEGY,
    CURVEEFFECT_STRATEGY
}eStrateyType;

typedef enum
{
    VIEW2D=0,
    VIEW3D
}eViewType;

typedef enum
{
    IMAGENODE=0,
    TEXTNODE,
    GROUPNODE,
    SOLIDNODE
}eNodeType;

typedef enum
{
    RGB=0,
    BGR,
    RGBA,
    BGRA
}eDataType;

typedef void* NODE_HANDLE;
typedef void* VIEW_HANDLE;

/*****************************************************************************************************************
 *
 *显示系统初始化api
 *
 *
*****************************************************************************************************************/

/*********************************************
* @name
* @param _width：画布宽度， _height：画布高度， _method：当前该参数必须为BRUSH_TOOL
* @return none
* @brief  渲染初始化gpu qt初始化
* @see
*********************************************/
void HASCOEngine_SystemCreate(unsigned int _width,unsigned int _height, eStatePattern _method);

/*********************************************
* @name
* @param
* @return 1：系统初始化完成   0：系统初始化未完成
* @brief  判断系统初始化是否已经完成，只有完成了初始化，才可以创建 view 与 node
* @see
*********************************************/
int HASCOEngine_GetTick();

/*********************************************
* @name
* @param
* @return none
* @brief  通知GPU重画画布
* @see
*********************************************/
void HASCOEngine_Invalidate();

/*********************************************
* @name
* @param _view：需要获取图像数据的区域   data: 图像数据存储的位置  RGB格式
* @return none
* @brief  need #define GET_DATA
* @see
*********************************************/
void HASCOEngine_GetData(NODE_HANDLE _view, unsigned char* _data);

/*********************************************
* @name
* @param _color：画布背景色
* @return
* @brief  设定画布的背景颜色
* @see
*********************************************/
void HASCOEngine_SetBackgroundColor(sColor _color);

/*********************************************
* @name
* @param _x：窗体的左下角X位置；_y：窗体的左下角Y坐标；_widht 窗体宽度；_height 窗体高度；_layer：窗体所处的层级，0位最下层；
_vt：窗体的种类，画2D场景为VIEW2D，画3D场景为VIEW3D
* @return
* @brief  设定view的位置，尺寸，场景属性
* @see
*********************************************/
VIEW_HANDLE HASCOEngine_View_Create(int _x, int _y, int _width, int _height, int _layer, eViewType _vt);

/*********************************************
* @name
* @param _view：窗体句柄；_x：窗体的左下角X位置；_y：窗体的左下角Y坐标；_widht 窗体宽度；_height 窗体高度
* @return
* @brief  设定view的尺寸与显示坐标系原点位置
* @see
*********************************************/
void HASCOEngine_View_SetRect(VIEW_HANDLE _view, int _x, int _y, int _width, int _height);

/*********************************************
* @name
* @param _view：窗体句柄；_alpha：窗体的透明度属性，会影响到其下所有的node，0全透明，1不透明
* @return
* @brief 更新视窗透明度
* @see
*********************************************/
void HASCOEngine_View_SetAlpha(VIEW_HANDLE _view, float _alpha);

/*********************************************
* @name
* @param _view：窗体句柄；_visible：HIDE不显示，SHOW显示
* @return
* @brief 修改视窗是否可见，当一个窗体区域不显示时，设定其visible为HIDE，这样做节省性能
* @see
*********************************************/
void HASCOEngine_View_SetVisible(VIEW_HANDLE _view, eShowStatus _visible);

/*********************************************
* @name
* @param _view：窗体句柄；_layer：数值越大越处于上层
* @return
* @brief 更新视窗图层
* @see
*********************************************/
void HASCOEngine_View_SetLayer(VIEW_HANDLE _view, int _layer);

/*********************************************
* @name
* @param _view_1：窗体句柄；_view_2：窗体句柄
* @return
* @brief 调换视窗图层
* @see
*********************************************/
void HASCOEngine_View_SwapLayer(VIEW_HANDLE _view_1, VIEW_HANDLE _view_2);

/*********************************************
* @name
* @param _view：窗体句柄
* @return
* @brief 获取窗体当前图层
* @see
*********************************************/
int HASCOEngine_View_GetLayer(VIEW_HANDLE _view);

/*********************************************
* @name
* @param _view：窗体句柄; _light:光照参数
* @return
* @brief 设置当前窗体光照效果
* @see
*********************************************/
void HASCOEngine_View_SetLightInfo(VIEW_HANDLE _view, sLightInfo _light);

/*********************************************
* @name
* @param _view：窗体句柄
* @return
* @brief 获取当前窗体光照效果
* @see
*********************************************/
sLightInfo HASCOEngine_View_GetLightInfo(VIEW_HANDLE _view);

/*********************************************
* @name
* @param _view：窗体句柄; _camera:相机参数
* @return
* @brief 设置当前窗体相机参数
* @see
*********************************************/
void HASCOEngine_View_SetCameraInfo(VIEW_HANDLE _view, sCameraInfo _camera);

/*********************************************
* @name
* @param _view：窗体句柄
* @return
* @brief 获取当前窗体相机参数
* @see
*********************************************/
sCameraInfo HASCOEngine_View_GetCameraInfo(VIEW_HANDLE _view);

/*********************************************
* @name
* @param _view：窗体句柄，node会绑定到该view上，view的opacity和位置会影响到其下的node；_url：图片源路径；p 顶点坐标数据存放位置，数据存储顺序为：左下角到右下角--左上角到右上角--左侧边缘从上到下--右侧边缘从上到下
_sideNum：上下两边点的数量；_insertNum：左右两边除顶点外点的数量。
_view：窗体句柄；_url：图片源路径；_x：图片左下角X坐标；_y：图片左下角Y坐标。
* @return HANDLE
* @brief  创建Imagenode。方式一：该方式创建的node外形有点列P确定   方式二：该方式穿件创建的node宽高由图形原本属性决定
* @see
*********************************************/
NODE_HANDLE HASCOEngine_Imagenode_Create(VIEW_HANDLE _view, char* _url, sPoint3f *p, int _sideNum, int _insertNum);
NODE_HANDLE HASCOEngine_Imagenode_Create_2(VIEW_HANDLE _view, char* _url, float _x, float _y);
NODE_HANDLE HASCOEngine_Imagenode_Create_3(NODE_HANDLE _groupnode, char* _url, sPoint3f *p, int _sideNum, int _insertNum);
NODE_HANDLE HASCOEngine_Imagenode_Create_4(NODE_HANDLE _groupnode, char* _url, float _x, float _y);

/*********************************************
* @name
* @param _view：窗体句柄，node会绑定到该view上，view的opacity和位置会影响到其下的node；p 顶点坐标数据存放位置，数据存储顺序为：左下角到右下角--左上角到右上角--左侧边缘从上到下--右侧边缘从上到下
_sideNum：上下两边点的数量；_insertNum：左右两边除顶点外点的数量；_fonturl：字库路径。
_view：窗体句柄；_x：图片左下角X坐标；_y：图片左下角Y坐标；_fonturl：字库路径。
* @return HANDLE
* @brief  创建Imagenode。方式一：该方式创建的textnode外形有点列P确定   方式二：该方式穿件创建的textnode宽高由node原本属性决定
* @see
*********************************************/
NODE_HANDLE HASCOEngine_Textnode_Create(VIEW_HANDLE _view, char* _string, sPoint3f *p, int _sideNum, int _insertNum, char* _fonturl);
NODE_HANDLE HASCOEngine_Textnode_Create_2(VIEW_HANDLE _view, char* _string, float _x, float _y, char* _fonturl);
NODE_HANDLE HASCOEngine_Textnode_Create_3(NODE_HANDLE _groupnode, char* _string, sPoint3f *p, int _sideNum, int _insertNum, char* _fonturl);
NODE_HANDLE HASCOEngine_Textnode_Create_4(NODE_HANDLE _groupnode, char* _string, float _x, float _y, char* _fonturl);

/*********************************************
* @name
* @param _view：窗体句柄，node会绑定到该view上，view的opacity和位置会影响到其下的node;
* @param _groupnode：node句柄，child node会绑定到该node上，parent node的opacity,位置,变换等会影响到其 child node。
* @return HANDLE
* @brief
* @see
*********************************************/
NODE_HANDLE HASCOEngine_Groupnode_Create(VIEW_HANDLE _view);
NODE_HANDLE HASCOEngine_Groupnode_Create_2(NODE_HANDLE _groupnode);

/*********************************************
* @name
* @param _view：窗体句柄，node会绑定到该view上，view的opacity和位置会影响到其下的node;
* @param _groupnode：node句柄，child node会绑定到该node上，parent node的opacity,位置,变换等会影响到其 child node。
* @return HANDLE
* @brief
* @see
*********************************************/
NODE_HANDLE HASCOEngine_Solidnode_Create(VIEW_HANDLE _view, char* _modelurl, char* _textureurl);
NODE_HANDLE HASCOEngine_Solidnode_Create_2(NODE_HANDLE _groupnode, char* _modelurl, char* _textureurl);

/*********************************************
* @name
* @param _node：从整个系统中删除掉该node，同时释放其占用的所有GPU CPU资源
* @return
* @brief  删除图像
* @see
*********************************************/
void HASCOEngine_Node_Delete(NODE_HANDLE _node);

/*********************************************
* @name
* @param _node：图形句柄；_url：图片源路径
* @return
* @brief 更新图像
* @see
*********************************************/
void HASCOEngine_Node_UpdateSource(NODE_HANDLE _node, char* _url);

/*********************************************
* @name
* @param _node：图形句柄；_data：图片数据源；_size：图像尺寸；_datatype：图像数据通道数，当前仅支持RGBA格式
* @return
* @brief 更新图像
* @see
*********************************************/
void HASCOEngine_Node_UpdateSourceFromData(NODE_HANDLE _node, unsigned char* _data, sRectSize _size, eDataType _datatype);

/*********************************************
* @name
* @param _node：图形句柄；
* @return
* @brief 获取imagenode源图片的宽高
* @see
*********************************************/
sRectSize HASCOEngine_Node_GetRect(NODE_HANDLE _node);

/*********************************************
* @name    deprecated
* @param _srcnode：图形句柄；_dstnode：图形句柄
* @return
* @brief 让 _dstnode 共享 _srcnode 在GPU中的图像资源
* @see
*********************************************/
void HASCOEngine_Node_UpdateSourceFromNode(NODE_HANDLE _srcnode, NODE_HANDLE _dstnode);

/*********************************************
* @name
* @param  _node：图形句柄；p 顶点坐标数据存放位置，数据存储顺序为：左下角到右下角--左上角到右上角--左侧边缘从上到下--右侧边缘从上到下
_sideNum：上下两边点的数量；_insertNum：左右两边除顶点外点的数量。
* @return
* @brief 通过点列更新node位姿,该方式可用于更改 imagenode textnode形状与位置,
*        该方式设定的是node的初始位置，建议使用transliate方式更改位置
* @see
*********************************************/
void HASCOEngine_Node_UpdatePosition(NODE_HANDLE _node, sPoint3f *p, int _sideNum, int _insertNum);

/*********************************************
* @name
* @param  _node：图形句柄；_x：左下角X坐标；_y：左下角Y坐标
* @return
* @brief 通过左下角设定node位置,该方式可用于更改 imagenode textnode位置,
*        该方式设定的是node的初始位置，建议使用transliate方式更改位置
* @see
*********************************************/
void HASCOEngine_Node_UpdatePosition_2(NODE_HANDLE _node, float _x, float _y);

/*********************************************
* @name
* @param  _node：图形句柄；_z：node显示的图层层级
* @return
* @brief 设定node在其所属view中显示层级，数值大显示在上面
* @see
*********************************************/
void HASCOEngine_Node_SetLayer(NODE_HANDLE _node, float _z);

/*********************************************
* @name
* @param  _node_1：图形句柄；_node_2：图形句柄
* @return
* @brief 交换两个node显示层级
* @see
*********************************************/
void HASCOEngine_Node_SwapLayer(NODE_HANDLE _node_1, NODE_HANDLE _node_2);

/*********************************************
* @name
* @param  _node：图形句柄
* @return
* @brief 获取图像图层
* @see
*********************************************/
float HASCOEngine_Node_GetLayer(NODE_HANDLE _node);

/*********************************************
* @name
* @param  _node：图形句柄；_visible：HIDE不显示，SHOW显示
* @return
* @brief 设定图像是否可见，当图像不可见时，设定visible为HIDE可以节省性能
* @see
*********************************************/
void HASCOEngine_Node_SetVisible(NODE_HANDLE _node, eShowStatus _visible);

/*********************************************
* @name
* @param  _node：图形句柄  _ST：形变参数
* @return
* @brief 该函数为变参函数
* @see
*  NORMAL_STRATEGY      : NODE_HANDLE _node, StrateyType _ST
*  GENIEEFFECT_STRATEGY : NODE_HANDLE _node, StrateyType _ST
*  WAVEEFFECT_STRATEGY  : NODE_HANDLE _node, StrateyType _ST
*  CURVEEFFECT_STRATEGY : NODE_HANDLE _node, StrateyType _ST, sPoint3 _ORIGIN
*********************************************/
void HASCOEngine_Node_SetMorph(NODE_HANDLE _node, eStrateyType _ST, ...);

/*********************************************
* @name
* @param  _node：图形句柄；_op：0为完全透明  1为完全不透明
* @return
* @brief 设定node的透明度
* @see
*********************************************/
void HASCOEngine_Node_SetOpacity(NODE_HANDLE _node, float _op);

/*********************************************
* @name
* @param  _node：图形句柄；_pivot：node做形变时的中心点
* @return
* @brief 设定node的中心点，node做缩放、旋转、平移时都是相对该点计算
* @see
*********************************************/
void HASCOEngine_Node_SetPivot(NODE_HANDLE _node, sPoint3f _pivot);

/*********************************************
* @name
* @param  _node：图形句柄；_translate：node平移参数。
* @return
* @brief 当平移为{0,0,0}时，node出现在初始值位置，采用右手坐标系，X轴指向右
* @see
*********************************************/
void HASCOEngine_Node_SetTranslate(NODE_HANDLE _node, sPoint3f _translate);

/*********************************************
* @name
* @param  _node：图形句柄；_angle：node旋转参数
* @return
* @brief node相对pivot点做绕X旋转变换，逆时针为正，弧度表示
* @see
*********************************************/
void HASCOEngine_Node_SetRotateX(NODE_HANDLE _node, float _angle);

/*********************************************
* @name
* @param _node：图形句柄；_angle：node旋转参数
* @return
* @brief node相对pivot点做绕Y旋转变换，逆时针为正，弧度表示
* @see
*********************************************/
void HASCOEngine_Node_SetRotateY(NODE_HANDLE _node, float _angle);

/*********************************************
* @name
* @param  _node：图形句柄；_angle：node旋转参数
* @return
* @brief node相对pivot点做绕Z旋转变换，逆时针为正，弧度表示
* @see
*********************************************/
void HASCOEngine_Node_SetRotateZ(NODE_HANDLE _node, float _angle);

/*********************************************
* @name
* @param  _node：图形句柄；_scale：缩放参数
* @return
* @brief 将Node相对pivot点做缩放
* @see
*********************************************/
void HASCOEngine_Node_SetScale(NODE_HANDLE _node, sPoint3f _scale);

/*********************************************
* @name
* @param   _node：图形句柄；_maskIndex：图像掩膜种类；_degree：掩膜参数
* @return none
* @brief 对 node 做掩膜变换  <0.0不做掩膜变换
* @see
*********************************************/
void HASCOEngine_Node_SetMaskEffect(NODE_HANDLE _node, NODE_HANDLE _masknode, float _degree);

/*********************************************
* @name
* @param  _node：图形句柄; _blendnode: 对图形做纹理融合; _degree: 纹理融合权重, 0.0--1.0;
* @return none
* @brief 对 node 做融合  <0.0不做融合   degree取值范围0.0--1.0
* @see
*********************************************/
void HASCOEngine_Node_SetBlendEffect(NODE_HANDLE _node, NODE_HANDLE _blendnode, float _degree);

/*********************************************
* @name
* @param _node：图形句柄; _string: 显示文字内容，unicode-8编码;
* @return
* @brief 更新图像
* @see
*********************************************/
void HASCOEngine_Node_SetFontString(NODE_HANDLE _node, char* _string);

/*********************************************
* @name
* @param  _node：图形句柄; _cl: 文字颜色;
* @return none
* @brief 若 node 为 textnode，该接口可用来设定文字颜色
* @see
*********************************************/
void HASCOEngine_Node_SetFontColor(NODE_HANDLE _node, sColor _cl);

/*********************************************
* @name
* @param  _node：图形句柄; _cl: 文字背景颜色;
* @return none
* @brief 若 node 为 textnode，该接口可用来设定文字背景颜色
* @see
*********************************************/
void HASCOEngine_Node_SetFontBackColor(NODE_HANDLE _node, sColor _cl, bool _enable);

/*********************************************
* @name
* @param  _node：图形句柄; _fonturl: 字库路径;
* @return none
* @brief 若 node 为 textnode，该接口可用来设定其ttf字库
* @see
*********************************************/
void HASCOEngine_Node_SetFontUrl(NODE_HANDLE _node, char* _fonturl);

/*********************************************
* @name
* @param  _node：图形句柄; _size: 文字大小，单位pixel;
* @return none
* @brief 若 node 为 textnode，该接口可用来设定其文字大小
* @see
*********************************************/
void HASCOEngine_Node_SetFontSize(NODE_HANDLE _node, int _size);

/*********************************************
* @name
* @param  _node：图形句柄; _size: 文字背框大小;
* @return none
* @brief 若 node 为 textnode，该接口可用来设定其文字背框大小
* @see
*********************************************/
void HASCOEngine_Node_SetFontBackRectSize(NODE_HANDLE _node, sRectSize _size);

/*********************************************
* @name
* @param  _node：图形句柄; _value: 文字左侧距离其背框距离;
* @return none
* @brief 若 node 为 textnode，该接口可用来设定其文字左侧边缘距离其背框大小
* @see
*********************************************/
void HASCOEngine_Node_SetFontHorizontalOffset(NODE_HANDLE _node, int _value);

/*********************************************
* @name
* @param  _node：图形句柄; _value: 文字上侧距离其背框距离;
* @return none
* @brief 若 node 为 textnode，该接口可用来设定其文字上侧边缘距离其背框大小
* @see
*********************************************/
void HASCOEngine_Node_SetFontVerticalOffset(NODE_HANDLE _node, int _value);

/*********************************************
* @name
* @param  _node：图形句柄; _value: 文字与其背景框的对齐方式;
* @return none
* @brief 若 node 为 textnode，该接口可用来设定其文字与其背景框的对齐方式
* 8位二进制数,分别对应：0位在最右侧
* 第0位   LeftAlignment
* 第1位   RightAlignment
* 第2位   HorizontalAlignment
* 第5位   TopAlignment
* 第6位   BottomAlignment
* 第7位   VerticalAlignment
* 可以叠加使用
* @see
*********************************************/
void HASCOEngine_Node_SetFontAlignment(NODE_HANDLE _node, int _value);

/*********************************************
* @name
* @param  _node：图形句柄;
* @return none
* @brief 若 node 为 textnode，该接口可用来获取文字宽度，单位为pixel
* @see
*********************************************/
int HASCOEngine_Node_GetFontWidth(NODE_HANDLE _node);

/*********************************************
* @name
* @param  _node：图形句柄;
* @return none
* @brief 若 node 为 textnode，该接口可用来获取文字高度，单位为pixel
* @see
*********************************************/
int HASCOEngine_Node_GetFontHeight(NODE_HANDLE _node);

/*********************************************
* @name   deprecated
* @param _srcnode: source image tobe cloned; _dstnode: cloned image ;
* @return none
* @brief    clone a image, this method can make node creation much more quick and can save memories;
*           this is a shadow copy, when one node was deleted, all other cloned ones will be affected
* @see
*********************************************/
void HASCOEngine_Node_Clone(NODE_HANDLE _srcnode, NODE_HANDLE _dstnode);

/*********************************************
* @name
* @param  _node：图形句柄; _material: 设置材质参数
* @return none
* @brief 若 node 为 solidnode，该接口可设置其材质参数
* @see
*********************************************/
void HASCOEngine_Node_SetMaterial(NODE_HANDLE _node, sMaterialInfo _material);

/*********************************************
* @name
* @param  _node：图形句柄
* @return none
* @brief 若 node 为 solidnode，该接口可获取其材质参数
* @see
*********************************************/
sMaterialInfo HASCOEngine_Node_GetMaterial(NODE_HANDLE _node);

/*********************************************
* @name  deprecated
* @param  _node：图形句柄; _modelurl: 设置node模型
* @return none
* @brief 若 node 为 solidnode，该接口可设置设置node模型
* @see
*********************************************/
void HASCOEngine_Node_SetModel(NODE_HANDLE _node, char* _modelurl);





#ifdef __cplusplus
}
#endif


#endif // GRAPHEGINE_H
