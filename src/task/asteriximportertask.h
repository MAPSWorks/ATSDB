/*
 * This file is part of ATSDB.
 *
 * ATSDB is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ATSDB is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with ATSDB.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ASTERIXIMPORTERTASK_H
#define ASTERIXIMPORTERTASK_H

#include "configurable.h"
#include "json.hpp"
#include "jsonparsingschema.h"
#include "asterixdecodejob.h"
#include "asterixextractrecordsjob.h"
#include "jsonmappingjob.h"

#include <QObject>

#include <memory>

#include "boost/date_time/posix_time/posix_time.hpp"

#include <tbb/concurrent_queue.h>

class TaskManager;
class ASTERIXImporterTaskWidget;
class ASTERIXCategoryConfig;
class SavedFile;
class QMessageBox;

namespace jASTERIX
{
    class jASTERIX;
}

class ASTERIXImporterTask: public QObject, public Configurable
{
    Q_OBJECT

public slots:
    void decodeASTERIXDoneSlot ();
    void decodeASTERIXObsoleteSlot ();
    void addDecodedASTERIXSlot (std::shared_ptr<nlohmann::json> data); // moved out from reference

    void extractASTERIXDoneSlot ();
    void extractASTERIXObsoleteSlot ();

    void mapJSONDoneSlot ();
    void mapJSONObsoleteSlot ();

    void insertProgressSlot (float percent);
    void insertDoneSlot (DBObject& object);

public:
    ASTERIXImporterTask(const std::string& class_id, const std::string& instance_id,
                        TaskManager* task_manager);
    virtual ~ASTERIXImporterTask();

    ASTERIXImporterTaskWidget* widget();

    virtual void generateSubConfigurable (const std::string &class_id, const std::string &instance_id);

    bool canImportFile (const std::string& filename);
    void importFile (const std::string& filename, bool test);

    const std::map <std::string, SavedFile*> &fileList () { return file_list_; }
    bool hasFile (const std::string &filename) { return file_list_.count (filename) > 0; }
    void addFile (const std::string &filename);
    void removeCurrentFilename ();
    void currentFilename (const std::string last_filename) { current_filename_ = last_filename; }
    const std::string &currentFilename () { return current_filename_; }

    std::shared_ptr<jASTERIX::jASTERIX> jASTERIX() { return jasterix_; }
    void refreshjASTERIX();

    const std::string& currentFraming() const;

    void currentFraming(const std::string &current_framing);

    bool hasConfiguratonFor (const std::string& category);
    bool decodeCategory (const std::string& category);
    void decodeCategory (const std::string& category, bool decode);
    std::string editionForCategory (const std::string& category);
    void editionForCategory (const std::string& category, const std::string& edition);

    std::shared_ptr<JSONParsingSchema> schema() const;

    bool debug() const;
    void debug(bool debug);

protected:
    bool debug_jasterix_;
    std::shared_ptr<jASTERIX::jASTERIX> jasterix_;

    std::map <std::string, SavedFile*> file_list_;
    std::string current_filename_;
    std::string current_framing_;

    std::string filename_;
    bool test_ {false};

    std::unique_ptr<ASTERIXImporterTaskWidget> widget_;

    std::map <std::string, ASTERIXCategoryConfig> category_configs_;

    std::shared_ptr<JSONParsingSchema> schema_;

    std::shared_ptr<ASTERIXDecodeJob> decode_job_;
    tbb::concurrent_queue <std::shared_ptr<ASTERIXExtractRecordsJob>> extract_jobs_;
    tbb::concurrent_queue <std::shared_ptr <JSONMappingJob>> json_map_jobs_;
    std::map <std::string, std::shared_ptr<Buffer>> buffers_;

    bool error_ {false};
    std::string error_message_;

    QMessageBox* msg_box_ {nullptr};

    size_t num_frames_ {0};
    size_t num_records_ {0};
    size_t records_mapped_ {0};
    size_t records_not_mapped_ {0};
    size_t records_created_ {0};
    size_t records_inserted_ {0};

    std::map<unsigned int, size_t> category_counts_;
    size_t key_count_ {0};
    size_t insert_active_ {0};

    std::set <int> added_data_sources_;

    bool all_done_{false};

    boost::posix_time::ptime start_time_;
    boost::posix_time::ptime stop_time_;

    virtual void checkSubConfigurables ();

    void insertData ();
    void checkAllDone ();


    void updateMsgBox();
    bool maxLoadReached ();
};

#endif // ASTERIXIMPORTERTASK_H