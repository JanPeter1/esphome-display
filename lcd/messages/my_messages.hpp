#ifndef MY_MESSAGES_H
#define MY_MESSAGES_H

// color constants

static const lv_color_t red    = lv_color_make(255, 0, 0);
static const lv_color_t green  = lv_color_make(0, 255, 0);
static const lv_color_t blue   = lv_color_make(0, 0, 255);
static const lv_color_t white  = lv_color_make(255, 255, 255);
static const lv_color_t yellow = lv_color_make(255, 255, 0);
static const lv_color_t purple = lv_color_make(255, 0, 255);
static const lv_color_t cyan   = lv_color_make(0, 255, 255);
static const lv_color_t black  = lv_color_make(0, 0, 0);
static const lv_color_t gray   = lv_color_make(128, 128, 128);


void set_label(lv_obj_t *label, const std::string &text, const lv_color_t color = white)
{
    lv_label_set_text(label, text.c_str());
    lv_obj_set_style_text_color(label, color, LV_PART_MAIN);
}

/// Notifications (mapping from string to label)

std::map<std::string, std::list<lv_obj_t *>> allNotifications = {};

/*
lv_obj_tree_walk_res_t _notif_initCallback(lv_obj_t *obj, void *userData) {
    if (lv_obj_check_type(obj, &lv_label_class)) {
        lv_label_t *label = reinterpret_cast<lv_label_t *>(obj);
        if (label->text[0] == '#') {
            allNotifications[label->text + 1].push_back(obj);
            lv_label_set_text(obj, " ");
        }
    }
    return LV_OBJ_TREE_WALK_NEXT;
}

void notif_initialize(lv_obj_t *root) {
    lv_obj_tree_walk(root, _notif_initCallback, nullptr);
}

void notif_initialize(lvgl::LvPageType *page) {
    lv_obj_tree_walk(page->obj, _notif_initCallback, nullptr);
}
*/

void notif_set_text(std::string id, std::string text, lv_color_t color = white) {
    for (auto label: allNotifications[id]) {
        lv_label_set_text(label, text.c_str());
        lv_obj_set_style_text_color(label, color, LV_PART_MAIN);
    }
}

void notif_set_color(std::string id, lv_color_t color) {
    for (auto label: allNotifications[id]) {
        lv_obj_set_style_text_color(label, color, LV_PART_MAIN);
    }
}

void notif_set(std::string id, std::string name, std::string icon, std::string text, lv_color_t color = white) {
    notif_set_text(id + "_name", name, color);
    notif_set_text(id + "_icon", icon);
    notif_set_text(id + "_text", text, color);
}

void notif_init(const std::string &id, lv_obj_t *lname = nullptr, lv_obj_t *licon = nullptr, lv_obj_t *ltext = nullptr) {
    if (nullptr != lname) allNotifications[id + "_name"].push_back(lname);
    if (nullptr != licon) allNotifications[id + "_icon"].push_back(licon);
    if (nullptr != ltext) allNotifications[id + "_text"].push_back(ltext);
}


/// Warning messages (shown sorted in the message_card)

struct DisplayMessage
{
    int Compare(const DisplayMessage &dm) const {
        return
            (priority > dm.priority)    ? -1:
            (priority < dm.priority)    ?  1:
            (id       > dm.id)          ?  1:
            (id       < dm.id)          ? -1:
            (pos      > dm.pos)         ?  1:
            (pos      < dm.pos)         ? -1:
                                           0;
    }

    bool operator == (const DisplayMessage& dm) const {
        return !Compare(dm);
    }

    bool operator < (const DisplayMessage& dm) const {
        return Compare(dm) < 0;   
    }

    std::string id = "";
    std::string text = "";
    std::string icon = "";
    int priority = 0;
    int pos = 0;
};
std::map<std::string, std::list<DisplayMessage>> allMessages = {};

void warn_clear(const std::string id)
{
    allMessages[id].clear();
}

void warn_add(const std::string id, const std::string &text, const std::string &icon, const int priority)
{
    DisplayMessage m;
    m.id = id;
    m.text = text;
    m.icon = icon;
    m.priority = priority;
    m.pos = allMessages[id].size();
    allMessages[id].push_back(m);
}

void warn_set(const std::string id, const std::string &text, const std::string &icon, const int priority)
{
    warn_clear(id);
    warn_add(id, text, icon, priority);
}

std::multiset<DisplayMessage> warn_get_sorted()
{
    std::multiset<DisplayMessage> ret;
    for (auto ldm: allMessages) {
        for (auto dm: ldm.second) {
            ret.insert(dm);
        }
    }
    return ret;
}

#endif // MY_MESSGES_H