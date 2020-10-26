const v11 = require('../../bazel-bin/v11/core/v11.js');
let keys = new Set();

v11.keyboard.addEventListener('press', (event) => {
    keys.add(event.key);
    if (keys.size === 2 && keys.has(55) && keys.has(35)) {
        const chrome = v11.system.getApplicationByName("Google Chrome");
        const tabs = chrome.getElementsByType("tabgroup")[0].children.slice(0, -1);
        for (const tab of tabs) {
            tab.actions.showmenu();
            v11.keyboard.pressKeys([35, 29, 48]);
        }
        process.exit();
    }
});

v11.keyboard.addEventListener('release', (event) => {
    keys.delete(event.key);
});
