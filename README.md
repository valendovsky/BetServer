# BetServer
### The application for manual fixation of tennis match statistics through a browser

The program runs in Windows and Windows Server operating systems.
You need to use OpenVPN or WireGuard for security when connecting.
The program is a websocket server built on the uWebSockets library.
Users are connected to the server through the browser.
Users record the match statistics using the page provided.

Some of the server commands are hidden.
You need to provide your own set of commands for proper operation of the program.
Some commands, such as password hashing, are for informational purposes, and they should be replaced.

The list of registered users and tennis matches for analysis are provided to the server in the form of files in CSV format.
Sample files in the Example folder.

---

### Программа для мануальной фиксации статистики теннисных матчей через браузер.

Программа работает на операционных системах Windows и Windows Server.
В целях безопасности предполагается доступ пользователей к приложению через отдельно установленные OpenVPN или WireGuard.
Программа представляет собой вебсокет сервер, построенный на библиотеке uWebSockets.
Пользователи подключаются к серверу через браузер и фиксируют статистику матча через предоставляемую страницу.

Часть команд сервера скрыта, для адекватной работы программы вам необходимо предоставить свой набор команд.
Некоторые команды, например, хэширование паролей, носят ознакомительный характер, и их стоит заменить.

Список зарегистрированных пользователей и теннисных матчей для разбора предоставляются серверу в виде файлов в формате csv.
Примеры файлов в папке Example.
