#include <iostream>
#include <glibmm.h>
#include "nmv-i-debugger.h"
#include "nmv-initializer.h"
#include "nmv-safe-ptr-utils.h"
#include "nmv-dynamic-module.h"

using namespace std ;
using namespace nemiver;
using namespace nemiver::common ;

void
on_engine_died_signal ()
{
    cout << "!!!!!engine died!!!!\n" ;
}

void
display_help ()
{
    cout << "test-basic <prog-to-debug>\n" ;
}

int
main (int argc, char *argv[])
{
    if (argc != 2) {
        display_help () ;
        return -1 ;
    }

    UString prog_to_debug = argv[1] ;

    try {
        Initializer::do_init () ;
        Glib::RefPtr<Glib::MainLoop> loop =
            Glib::MainLoop::create (Glib::MainContext::get_default ()) ;

        THROW_IF_FAIL (loop) ;

        DynamicModuleManager module_manager ;

        UString p = DBG_PERSPECTIVE_PLUGIN_PATH ;
        module_manager.module_loader ()->config_search_paths ().push_back (p) ;

        IDebuggerSafePtr debugger =
                    module_manager.load<IDebugger> ("gdbengine") ;

        debugger->set_event_loop_context (loop->get_context ()) ;

        debugger->engine_died_signal ().connect
                (sigc::ptr_fun (&on_engine_died_signal)) ;

        vector<UString> args, source_search_dir ;
        args.push_back (prog_to_debug) ;
        source_search_dir.push_back (".") ;

        debugger->load_program (args, source_search_dir);
        sleep (1) ;
        debugger->set_breakpoint ("main") ;
        sleep (1) ;
        debugger->run () ;
        sleep (1) ;
        debugger->set_breakpoint ("func1") ;
        sleep (1) ;
        debugger->set_breakpoint ("func2") ;
        sleep (1) ;
        debugger->list_breakpoints () ;
        sleep (1) ;
        debugger->do_continue () ;
        sleep (1) ;
        cout << "nb of breakpoints: "
             << debugger->get_cached_breakpoints ().size ()
             << "\n" ;
        debugger->do_continue () ;
        sleep (1) ;
        debugger->run_loop_iterations (-1) ;
    } catch (Glib::Exception &e) {
        LOG_ERROR ("got error: " << e.what () << "\n") ;
        return -1 ;
    } catch (exception &e) {
        LOG_ERROR ("got error: " << e.what () << "\n") ;
        return -1 ;
    } catch (...) {
        LOG_ERROR ("got an unknown error\n") ;
        return -1 ;
    }
    return 0 ;
}
