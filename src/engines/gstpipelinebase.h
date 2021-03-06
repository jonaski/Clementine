/* This file is part of Clementine.
   Copyright 2021, Jim Broadus <jbroadus@gmail.com>

   Clementine is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Clementine is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Clementine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GSTPIPELINEBASE_H
#define GSTPIPELINEBASE_H

#include <gst/gst.h>

#include <QObject>
#include <QStandardItemModel>

class GstPipelineBase : public QObject {
 public:
  GstPipelineBase(const QString& type);
  virtual ~GstPipelineBase();

  virtual bool Init();

  // Globally unique across all pipelines.
  int id() const { return id_; }

  void DumpGraph();

 protected:
  GstElement* pipeline_;

 private:
  const QString type_;

  // Using == to compare two pipelines is a bad idea, because new ones often
  // get created in the same address as old ones.  This ID will be unique for
  // each pipeline.
  static std::atomic<int> sId;
  const int id_;
};

class GstPipelineModel : public QStandardItemModel {
  Q_OBJECT

 public:
  explicit GstPipelineModel(QObject* parent = nullptr);
  void AddPipeline(int id, const QString& name);
  void RemovePipeline(int id);

 private:
  friend class PipelineView;
  int GetPipelineId(const QModelIndex& index) const;

 private:
  int FindRowById(int id) const;

  enum Role { Role_Id = Qt::UserRole + 1 };
};

#endif  // GSTPIPELINEBASE_H
