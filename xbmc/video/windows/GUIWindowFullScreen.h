#pragma once

/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "guilib/GUIWindow.h"
#include "threads/CriticalSection.h"

enum SubtitleAlign
{
  SUBTITLE_ALIGN_MANUAL         = 0,
  SUBTITLE_ALIGN_BOTTOM_INSIDE,
  SUBTITLE_ALIGN_BOTTOM_OUTSIDE,
  SUBTITLE_ALIGN_TOP_INSIDE,
  SUBTITLE_ALIGN_TOP_OUTSIDE
};

class CGUITextLayout; // forward

class CGUIWindowFullScreen : public CGUIWindow
{
public:
  CGUIWindowFullScreen(void);
  virtual ~CGUIWindowFullScreen(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
  virtual void FrameMove();
  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregion);
  virtual void Render();
  virtual void OnWindowLoaded();
  void ChangetheTimeCode(int remote);
  void ChangetheTVGroup(bool next);

protected:
  virtual EVENT_RESULT OnMouseEvent(const CPoint &point, const CMouseEvent &event);

private:
  void RenderTTFSubtitles();
  void SeekChapter(int iChapter);
  void FillInTVGroups();
  void ToggleOSD();

  enum SEEK_TYPE { SEEK_ABSOLUTE, SEEK_RELATIVE };
  enum SEEK_DIRECTION { SEEK_FORWARD, SEEK_BACKWARD };

  /*! \brief Seek to the current time code stamp, either relative or absolute
   \param type - whether the seek is absolute or relative
   \param direction - if relative seeking, which direction to seek
   */
  void SeekToTimeCodeStamp(SEEK_TYPE type, SEEK_DIRECTION direction = SEEK_FORWARD);

  /*! \brief Convert the current timecode into a time in seconds to seek
   */
  double GetTimeCodeStamp();

  bool m_bShowViewModeInfo;
  unsigned int m_dwShowViewModeTimeout;
  CGUIInfoBool m_showCodec;

  bool m_bShowCurrentTime;

  bool m_bGroupSelectShow;
  bool m_timeCodeShow;
  unsigned int m_timeCodeTimeout;
  int m_timeCodeStamp[6];
  int m_timeCodePosition;
  
  CCriticalSection m_fontLock;
  CGUITextLayout* m_subsLayout;
};
