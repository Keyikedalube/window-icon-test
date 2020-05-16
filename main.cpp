#include <gtkmm.h>

class WindowIconTest : public Gtk::Window {
        public:
                WindowIconTest();
                ~WindowIconTest();
        private:
                Glib::RefPtr<Gtk::Builder> window_content;
                Glib::RefPtr<Gdk::Pixbuf> window_icon;
};

WindowIconTest::WindowIconTest()
{
        window_content = Gtk::Builder::create_from_resource("/io/github/window-icon-test/window_content.glade");
        window_icon = Gdk::Pixbuf::create_from_resource("/io/github/window-icon-test/synfig_icon.png");

        Gtk::Grid *grid = nullptr;
        window_content->get_widget("grid", grid);

        Gtk::Image *image = nullptr;
        window_content->get_widget("image", image);
        image->set_from_resource("/io/github/window-icon-test/synfig_icon.png");

        set_icon(window_icon);
        add(*grid);
}

WindowIconTest::~WindowIconTest()
{
}

int main()
{
        Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("io.github.window-icon-test");

        WindowIconTest window;

        return app->run(window);
}
