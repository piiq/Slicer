#ifndef __vtkSlicerAnnotationModuleLogic_h
#define __vtkSlicerAnnotationModuleLogic_h

// Annotation QT includes
#include "GUI/qSlicerAnnotationModuleWidget.h"

// Slicer Logic includes
#include "vtkSlicerModuleLogic.h"

// MRML includes
#include "vtkMRMLAnnotationHierarchyNode.h"
#include "vtkMRMLAnnotationSnapshotNode.h"

#include "qSlicerAnnotationModuleExport.h"

class Q_SLICER_QTMODULES_ANNOTATIONS_EXPORT vtkSlicerAnnotationModuleLogic :
  public vtkSlicerModuleLogic
{
public:

  static vtkSlicerAnnotationModuleLogic *New();
  vtkTypeRevisionMacro(vtkSlicerAnnotationModuleLogic,vtkSlicerModuleLogic);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Initialize listening to MRML events
  void InitializeEventListeners();

  // Start the place mode for annotations
  void StartPlaceMode();

  // Exit the place mode for annotations
  void StopPlaceMode();

  // Start adding a new annotation Node
  void AddAnnotationNode(const char * nodeDescriptor);

  // After a node was added, propagate to widget
  void AddNodeCompleted(vtkMRMLAnnotationHierarchyNode* hierarchyNode);

  // Cancel the current annotation placement or remove last annotation node
  void CancelCurrentOrRemoveLastAddedAnnotationNode();

  // Register the widget
  void SetAndObserveWidget(qSlicerAnnotationModuleWidget* widget);

  // MRML events
  void ProcessMRMLEvents(vtkObject *caller, unsigned long event, void *callData );
  void OnMRMLSceneNodeAddedEvent(vtkMRMLNode* node);
  void OnMRMLAnnotationNodeModifiedEvent(vtkMRMLNode* node);

  //
  // Annotation Properties (interface to MRML)
  //
  /// Register MRML Node classes to Scene. Gets called automatically when the MRMLScene is attached to this logic class.
  virtual void RegisterNodes();

  /// Get the name of an Annotation MRML node
  const char * GetAnnotationName(const char * id);

  /// Return the text of an Annotation MRML node
  vtkStdString GetAnnotationText(const char* id);
  /// Set the text of an Annotation MRML node
  void SetAnnotationText(const char* id, const char * newtext);

  /// Get the text scale of an Annotation MRML node
  double GetAnnotationTextScale(const char* id);
  /// Set the text scale of an Annotation MRML node
  void SetAnnotationTextScale(const char* id, double textScale);

  /// Get the selected text color of an Annotation MRML node
  double * GetAnnotationTextSelectedColor(const char* id);
  /// Set the selected text color of an Annotation MRML node
  void SetAnnotationTextSelectedColor(const char* id, double * color);

  /// Get the selected text color of an Annotation MRML node
  double * GetAnnotationTextUnselectedColor(const char* id);
  /// Set the selected text color of an Annotation MRML node
  void SetAnnotationTextUnselectedColor(const char* id, double * color);

  /// Get the measurement value of an Annotation MRML node
  const char * GetAnnotationMeasurement(const char * id, bool showUnits);

  /// Get the icon name of an Annotation MRML node
  const char * GetAnnotationIcon(const char * id);

  /// Get the lock flag of an Annotation MRML node
  int GetAnnotationLockedUnlocked(const char * id);
  /// Toggle the lock flag of an Annotation MRML node
  void SetAnnotationLockedUnlocked(const char * id);

  /// Get the visibility flag of an Annotation MRML node
  int GetAnnotationVisibility(const char * id);
  /// Toggle the visibility flag of an Annotation MRML node
  void SetAnnotationVisibility(const char * id);

  /// Set the selected flag of an Annotation MRML node
  void SetAnnotationSelected(const char * id, bool selected);

  /// Backup an Annotation MRML node
  void BackupAnnotationNode(const char * id);
  /// Restore a backup of an Annotation MRML node
  void RestoreAnnotationNode(const char * id);

  /// Restore view of an Annotation MRML node
  void RestoreAnnotationView(const char* id);

  //
  // Hierarchy functionality
  //
  /// Get the toplevel Annotation hierarchy node
  vtkMRMLAnnotationHierarchyNode* GetTopLevelHierarchyNode();

  /// Add a new Annotation hierarchy node
  vtkMRMLAnnotationHierarchyNode* AddNewHierarchyNode();

  //
  // SnapShot functionality
  //
  /// Create a snapShot. This includes a screenshot of a specific view (see \ref GrabScreenShot(int screenshotWindow)),
  /// a multiline text description and the creation of a Scene SnapShot.
  void CreateSnapShot(const char* name, const char* description, int screenshotType, vtkImageData* screenshot);

  /// Modify an existing snapShot.
  void ModifySnapShot(const char* id, const char* name, const char* description, int screenshotType, vtkImageData* screenshot);

  /// Convert a QImage to a vtkImageData
  bool QImageToVtkImageData(const QImage& img, vtkImageData* vtkimage);

  /// Convert a vtkImageData to a QImage
  bool VtkImageDataToQImage(vtkImageData* vtkimage, QImage& img);

  /// Return the name of an existing annotation snapShot.
  vtkStdString GetSnapShotName(const char* id);

  /// Return the description of an existing annotation snapShot.
  vtkStdString GetSnapShotDescription(const char* id);

  /// Return the screenshotType of an existing annotation snapShot.
  int GetSnapShotScreenshotType(const char* id);

  /// Return the screenshot of an existing annotation snapShot.
  vtkImageData* GetSnapShotScreenshot(const char* id);

  /// Restore an annotation snapShot.
  void RestoreSnapShot(const char* id);

  /// Callback when an annotation snapShot node was added.
  void OnMRMLSceneSnapShotNodeAdded(vtkMRMLAnnotationSnapshotNode* snapshotNode);

  /// Callback when an annotation snapShot node was modified.
  void OnMRMLSceneSnapShotNodeModified(vtkMRMLAnnotationSnapshotNode* snapshotNode);

  /// Callback when an annotation snapShot node was modified.
  void OnMRMLSceneSnapShotNodeRemoved(vtkMRMLAnnotationSnapshotNode* snapshotNode);

  /// Check if node id corresponds to a snapShot node
  bool IsSnapshotNode(const char* id);

protected:

  vtkSlicerAnnotationModuleLogic();

  virtual ~vtkSlicerAnnotationModuleLogic();

private:

  qSlicerAnnotationModuleWidget* m_Widget;

  vtkMRMLAnnotationNode* m_LastAddedAnnotationNode;

  vtkMRMLAnnotationHierarchyNode* m_ActiveHierarchy;

  vtksys_stl::string m_StringHolder;

};

#endif
