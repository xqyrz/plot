#ifndef QVAPPLICATION_H
#define QVAPPLICATION_H

#include "imageview.h"
#include "settingsmanager.h"
#include "shortcutmanager.h"
#include "actionmanager.h"
#include "updatechecker.h"
#include "qvoptionsdialog.h"
#include "qvaboutdialog.h"
#include "qvwelcomedialog.h"

#include <QApplication>
#include <QRegularExpression>

#if defined(qvApp)
#  undef qvApp
#endif

#define qvApp  (QVApp::instance())

#define qvGetSettingBool(setting) \
    qvApp->getSettingsManager()->getBool(SettingsManager::Setting::setting)
#define qvGetSettingInt(setting) \
    qvApp->getSettingsManager()->getInt(SettingsManager::Setting::setting)
#define qvGetSettingDouble(setting) \
    qvApp->getSettingsManager()->getDouble(SettingsManager::Setting::setting)
#define qvGetSettingString(setting) \
    qvApp->getSettingsManager()->getString(SettingsManager::Setting::setting)

class QVApp : public QObject
{
    Q_OBJECT
private:
    explicit QVApp(QObject *parent = nullptr);
public:
   static QVApp* instance();
    ~QVApp() override;

    bool event(QEvent *event) override;

    static void openFile(ImageView *window, const QString &file, bool resize = true);

    static void openFile(const QString &file, bool resize = true);

    static void pickFile(ImageView *parent = nullptr);

    static void pickUrl(ImageView *parnet = nullptr);

    static ImageView *newWindow();

    ImageView *getMainWindow(bool shouldBeEmpty);

    void checkUpdates(bool isStartupCheck);

    void checkedUpdates();

    void recentsMenuUpdated();

    void addToLastActiveWindows(ImageView *window);

    void deleteFromLastActiveWindows(ImageView *window);

    void openOptionsDialog(QWidget *parent = nullptr);

    void openWelcomeDialog(QWidget *parent = nullptr);

    void openAboutDialog(QWidget *parent = nullptr);

    void hideIncompatibleActions();

    void defineFilterLists();

    QMenuBar *getMenuBar() const { return menuBar; }

    const QStringList &getNameFilterList() const { return nameFilterList; }

    const QStringList &getFileExtensionList() const { return fileExtensionList; }

    const QStringList &getMimeTypeNameList() const { return mimeTypeNameList; }

    SettingsManager *getSettingsManager() { return settingsManager; }

    ShortcutManager *getShortcutManager() { return shortcutManager; }

    ActionManager *getActionManager() { return actionManager; }

    void ensureFontLoaded(const QString &path);

    static QIcon iconFromFont(const QString &fontFamily, const QChar &codePoint, const int pixelSize, const qreal pixelRatio);

    static qreal getPerceivedBrightness(const QColor &color);

private:
    QList<ImageView *> lastActiveWindows;

    QMenu *dockMenu;

    QMenuBar *menuBar;

    QStringList nameFilterList;
    QStringList fileExtensionList;
    QStringList mimeTypeNameList;

    // This order is very important
    SettingsManager* settingsManager;
    ActionManager* actionManager;
    ShortcutManager* shortcutManager;

    QPointer<QVOptionsDialog> optionsDialog;
    QPointer<QVWelcomeDialog> welcomeDialog;
    QPointer<QVAboutDialog> aboutDialog;

#ifndef QV_DISABLE_ONLINE_VERSION_CHECK
    UpdateChecker updateChecker;
#endif // QV_DISABLE_ONLINE_VERSION_CHECK

    QSet<QString> loadedFontPaths;
};

#endif // QVAPPLICATION_H
