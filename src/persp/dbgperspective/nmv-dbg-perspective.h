//Author: Dodji Seketeli
/*
 *This file is part of the Nemiver project
 *
 *Nemiver is free software; you can redistribute
 *it and/or modify it under the terms of
 *the GNU General Public License as published by the
 *Free Software Foundation; either version 2,
 *or (at your option) any later version.
 *
 *Nemiver is distributed in the hope that it will
 *be useful, but WITHOUT ANY WARRANTY;
 *without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *See the GNU General Public License for more details.
 *
 *You should have received a copy of the
 *GNU General Public License along with Nemiver;
 *see the file COPYING.
 *If not, write to the Free Software Foundation,
 *Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 *See COPYRIGHT file copyright information.
 */
#ifndef __NMV_DBG_PERSPECTIVE_H__
#define __NMV_DBG_PERSPECTIVE_H__

#include <list>
#include "nmv-i-perspective.h"
#include "nmv-i-debugger.h"
#include "nmv-sess-mgr.h"
#include <sigc++/trackable.h>

namespace gtksourceview {
    class SourceBuffer;
}

NEMIVER_BEGIN_NAMESPACE (nemiver)

class SourceEditor;
class NEMIVER_API IDBGPerspective : public IPerspective {
    //non copyable
    IDBGPerspective (const IPerspective&);
    IDBGPerspective& operator= (const IPerspective&);

public:

    IDBGPerspective (DynamicModule *a_dynmod) :
        IPerspective (a_dynmod)
    {
    }

    virtual ~IDBGPerspective () {};

    virtual void do_init (IWorkbench *a_workbench)  = 0;

    virtual const UString& get_perspective_identifier () = 0;

    virtual void get_toolbars (list<Gtk::Widget*> &a_tbs) = 0;

    virtual Gtk::Widget* get_body () = 0;

    virtual IWorkbench& get_workbench () = 0;

    virtual void edit_workbench_menu () = 0;

    virtual void open_file () = 0;

    virtual bool open_file (const UString &a_uri,
                            int current_line=-1)= 0;

    virtual void close_current_file () = 0;

    virtual void close_file (const UString &a_uri) = 0;

    virtual Gtk::Widget* load_menu (const UString &a_filename,
                                    const UString &a_widget_name) = 0;

    virtual void close_opened_files () = 0;

    virtual ISessMgr& session_manager () = 0;

    virtual void execute_session (ISessMgr::Session &a_session) = 0;

    virtual void execute_program () = 0;

    virtual void execute_program (const UString &a_prog,
                          const vector<UString> &a_args,
                          const map<UString, UString> &a_env,
                          const UString &a_cwd = ".",
                          bool a_close_opened_files = false) = 0;

    virtual void execute_program (const UString &a_prog,
                                  const vector<UString> &a_args,
                                  const map<UString, UString> &a_env,
                                  const UString &a_cwd,
                                  const vector<IDebugger::Breakpoint>
                                                                  &a_breaks,
                                  bool a_check_is_new_program = true,
                                  bool a_close_opened_files = false) = 0;

    virtual void attach_to_program (unsigned int a_pid,
                                    bool a_close_open_files = false) = 0;

    virtual void load_core_file () = 0;

    virtual void load_core_file (const UString &a_prog_path,
                                 const UString &a_core_file_path) = 0;

    virtual void run () = 0;

    virtual void step_over () = 0;

    virtual void step_into () = 0;

    virtual void step_out () = 0;

    virtual void do_continue () = 0;

    virtual void set_breakpoint () = 0;

    virtual void set_breakpoint (const UString &a_file,
                                 int a_line,
                                 const UString &a_condition,
				 bool a_is_count_point) = 0;

    virtual void set_breakpoint (const UString &a_func_name,
                                 const UString &a_condition,
				 bool a_is_count_point) = 0;

    virtual void set_breakpoint (const IDebugger::Breakpoint &a_breakpoint) = 0;

    virtual void append_breakpoints
            (const map<int, IDebugger::Breakpoint> &a_breaks) = 0;

    virtual bool get_breakpoint_number (const UString &a_file_name,
                                        int a_linenum,
                                        int &a_break_num,
                                        bool &a_enabled) = 0;

    virtual bool delete_breakpoint () = 0;

    virtual bool delete_breakpoint (int a_breakpoint_num) = 0;

    virtual bool delete_breakpoint (const UString &a_file_uri,
                                    int a_linenum) = 0;

    virtual IDebuggerSafePtr& debugger () = 0;

    virtual void add_text_to_command_view (const UString &a_text,
                                           bool a_no_repeat=true) = 0;

    virtual void add_text_to_target_output_view (const UString &a_text) = 0;

    virtual void add_text_to_log_view (const UString &a_text) = 0;

    virtual bool set_where (const UString &a_uri,
                            int line,
                            bool a_do_scroll=true) = 0;

    virtual Gtk::Widget* get_contextual_menu () = 0;

    virtual bool uses_launch_terminal () const = 0;

    virtual void uses_launch_terminal (bool a_flag) = 0;

    virtual sigc::signal<void, bool>& activated_signal () = 0;

    virtual sigc::signal<void, bool>& debugger_ready_signal () = 0;

    virtual bool agree_to_shutdown () = 0;
};//end class IDBGPerspective

NEMIVER_END_NAMESPACE (nemiver)
#endif //__NMV_DBG_PERSPECTIVE_H__
