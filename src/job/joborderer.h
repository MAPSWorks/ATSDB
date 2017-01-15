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

/*
 * JobOrderer.h
 *
 *  Created on: Feb 8, 2013
 *      Author: sk
 */

#ifndef JOBORDERER_H_
#define JOBORDERER_H_

#include <vector>
#include <boost/thread/mutex.hpp>

class Buffer;
class Job;

/**
 * @brief Allows a class to create Jobs
 *
 * Has simple functions that monitors active jobs, and a function that sets all active Jobs as obsolete.
 * Is thread-safe.
 */
class JobOrderer
{
public:
    /// @brief Constructor
    JobOrderer();
    /// @brief Destructor
    virtual ~JobOrderer();

    /// @brief Adds a Job to the active list
    void addJob (Job *job);
    /// @brief Removes a Job from the active list
    void removeJob (Job *job);
    /// @brief Sets all Jobs on the active list as obsolete
    void setJobsObsolete ();

protected:
    /// Container with all active jobs
    std::vector <Job *> active_jobs_;
    /// Protects the active jobs container
    boost::mutex mutex_;
};

#endif /* JOBORDERER_H_ */