#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>
#include <rectangle.h>
#include <vscene.h>

class AddCommand : public QUndoCommand
{
public:
    AddCommand(VScene *scene, VShape *shape,
                    QUndoCommand *parent = nullptr);
    void undo() override;
    void redo() override;

private:
    VScene *_scene;
    VShape *_shape;
    QString _shapeName;
};

class RemoveCommand : public QUndoCommand
{
public:
    RemoveCommand(VScene *scene, const QString &shapeName,
                       QUndoCommand *parent = nullptr);
    void undo() override;
    void redo() override;

private:
    VScene *_scene;
    VShape *_shape;
    QString _shapeName;
};

/*
class SetShapeColorCommand : public QUndoCommand
{
public:
    SetShapeColorCommand(VScene *scene, const QString &shapeName,
                         const QColor &color, QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

    bool mergeWith(const QUndoCommand *command) override;
    int id() const override;

private:
    VScene *_scene;
    QString _shapeName;
    QColor _oldColor;
    QColor _newColor;
};
*/
/*
class SetShapeRectCommand : public QUndoCommand
{
public:
    SetShapeRectCommand(VScene *scene, const QString &shapeName,
                        const QGraphicsItem &shape, QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

    bool mergeWith(const QUndoCommand *command) override;
    int id() const override;

private:
    VScene *_scene;
    QString _shapeName;
    QRect _oldRect;
    QRect _newRect;
};
*/

#endif // COMMANDS_H

