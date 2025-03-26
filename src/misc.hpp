#ifndef HK_POMODORO_COLORS_HPP
#define HK_POMODORO_COLORS_HPP

#include <QtQml/qqmlregistration.h>
#include <QAbstractItemModel>
#include <QObject>

#include <KAboutData>
#include <KColorSchemeManager>

class Misc : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  Q_PROPERTY(QAbstractItemModel* colorSchemes READ colorSchemes CONSTANT)

  Q_PROPERTY(int colorScheme READ colorScheme NOTIFY sigColorScheme)

  Q_PROPERTY(KAboutData aboutData READ aboutData CONSTANT)

 public:
  explicit Misc(QObject* parent = nullptr);

  [[nodiscard]] QAbstractItemModel* colorSchemes() const;

  [[nodiscard]] int colorScheme() const;
  Q_INVOKABLE void setColorScheme(int idx);
  Q_SIGNAL void sigColorScheme();

  KAboutData aboutData() const;

 private:
  KColorSchemeManager* m_color;
};

#endif
