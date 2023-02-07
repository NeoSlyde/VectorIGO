#ifndef VSHAPEVISITOR_H
#define VSHAPEVISITOR_H




class VRectangle;
class ellipse;

class VShapeVisitor
{
public:
    VShapeVisitor();
    virtual void visit( VRectangle* rectangle)  = 0;
    virtual void visit( ellipse* rectangle)  = 0;

};

#endif // VSHAPEVISITOR_H
