#ifndef UNDOCOMMANDS_H
#define UNDOCOMMANDS_H

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QUndoCommand>

template <typename T, typename spBox>
class spinBoxUndoCommand : public QUndoCommand
{
public:

    enum { Id = 815}; //id of this undocommand
    spinBoxUndoCommand(T newValue,
                      T oldValue,
                      spBox *spinBox,
                      QUndoCommand *parent = nullptr);
    ~spinBoxUndoCommand() override = default;

    void undo() override;
    void redo() override;
    bool mergeWith(const QUndoCommand *command) override;
    int id() const override { return Id; }


private:
    /* The variable _isFirstRun is being tested in "redo()".
       If true, will not set spinbox value. This is needed to not
       interrupt user editing when the qundocommand is pushed onto
       the undo stack. When being pushed, as call to redo()
       is invoked.
       */
    bool _isFirstRun {true};
    T _newValue {0.0};
    T _oldValue {0.0};
    spBox *_spinBox;
};

#endif // UNDOCOMMANDS_H
