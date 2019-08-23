/* GENERATED HEADER, Don't modify!!! */
#ifndef PUSH2TOPOLOGY_H
#define PUSH2TOPOLOGY_H

#include "FpVector2D.h"
#include "FpGfxTypes.h"
#include "FpButton.h"
#include "FpButton3d.h"
#include "FpButton5d.h"
#include "FpEncoder.h"
#include "FpPotentiometer.h"
#include "FpTouchSurface.h"
#include <cstdint>
#include <string>

namespace fp
{

struct Push2Topology
{
struct Potentiometer
{
   enum Id
   {
      eLast = -1
   };

   static std::string id2Str(Id widgetId)
   {
        switch(widgetId)
        {
            default: return std::string();
        }
   }

   using WidgetType = fp::Potentiometer;

   static constexpr Vector2d<uint8_t> getDim(Id widgetId)
   {
      constexpr Vector2d<uint8_t> dim = {0,0};
      return dim;
   }

   static uint32_t getResolution(Id widgetId)
   {
      const uint32_t res = 0;
      return res;
   }
};

struct Led
{
   enum Id
   {
      eLedAddTrack = 0,
      eLedAccent = 1,
      eLedFixedLength = 2,
      eLedAddDevice = 3,
      eLedSession = 4,
      eLedSetup = 5,
      eLedMute = 6,
      eLedLeftArrow = 7,
      eLedConvert = 8,
      eLedStopClip = 9,
      eLedBrowse = 10,
      eLedRepeat = 11,
      eLedSolo = 12,
      eLedSel = 13,
      eLedShift = 14,
      eBtnSilLed = 15,
      eLedScale = 16,
      eLedPlay = 17,
      eLedDelete = 18,
      eLedNote = 19,
      eLedTapTempo = 20,
      eLedDevice = 21,
      eLedDownArrow = 22,
      eLedRightArrow = 23,
      eLedOctaveDown = 24,
      eLedPageLeft = 25,
      eLedMix = 26,
      eLedUndo = 27,
      eLedLayout = 28,
      eLedDuplicate = 29,
      eLedNew = 30,
      eLedQuantize = 31,
      eLedAutomate = 32,
      eLedSelect = 33,
      eLedPageRight = 34,
      eLedMetronome = 35,
      eLedUser = 36,
      eLedOctaveUp = 37,
      eLedT = 38,
      eTouchSurfaceLed = 39,
      eLedUpArrow = 40,
      eLedRecord = 41,
      eLedB = 42,
      eLedMaster = 43,
      eLedClip = 44,
      eLedDoubleLoop = 45,
      eLast = eLedDoubleLoop
   };

   static std::string id2Str(Id widgetId)
   {
        switch(widgetId)
        {
            case eLedAddTrack: return "LedAddTrack";
            case eLedAccent: return "LedAccent";
            case eLedFixedLength: return "LedFixedLength";
            case eLedAddDevice: return "LedAddDevice";
            case eLedSession: return "LedSession";
            case eLedSetup: return "LedSetup";
            case eLedMute: return "LedMute";
            case eLedLeftArrow: return "LedLeftArrow";
            case eLedConvert: return "LedConvert";
            case eLedStopClip: return "LedStopClip";
            case eLedBrowse: return "LedBrowse";
            case eLedRepeat: return "LedRepeat";
            case eLedSolo: return "LedSolo";
            case eLedSel: return "LedSel";
            case eLedShift: return "LedShift";
            case eBtnSilLed: return "BtnSilLed";
            case eLedScale: return "LedScale";
            case eLedPlay: return "LedPlay";
            case eLedDelete: return "LedDelete";
            case eLedNote: return "LedNote";
            case eLedTapTempo: return "LedTapTempo";
            case eLedDevice: return "LedDevice";
            case eLedDownArrow: return "LedDownArrow";
            case eLedRightArrow: return "LedRightArrow";
            case eLedOctaveDown: return "LedOctaveDown";
            case eLedPageLeft: return "LedPageLeft";
            case eLedMix: return "LedMix";
            case eLedUndo: return "LedUndo";
            case eLedLayout: return "LedLayout";
            case eLedDuplicate: return "LedDuplicate";
            case eLedNew: return "LedNew";
            case eLedQuantize: return "LedQuantize";
            case eLedAutomate: return "LedAutomate";
            case eLedSelect: return "LedSelect";
            case eLedPageRight: return "LedPageRight";
            case eLedMetronome: return "LedMetronome";
            case eLedUser: return "LedUser";
            case eLedOctaveUp: return "LedOctaveUp";
            case eLedT: return "LedT";
            case eTouchSurfaceLed: return "TouchSurfaceLed";
            case eLedUpArrow: return "LedUpArrow";
            case eLedRecord: return "LedRecord";
            case eLedB: return "LedB";
            case eLedMaster: return "LedMaster";
            case eLedClip: return "LedClip";
            case eLedDoubleLoop: return "LedDoubleLoop";
            default: return std::string();
        }
   }

   static constexpr Vector2d<uint8_t> getDim(Id widgetId) noexcept
   {
      constexpr Vector2d<uint8_t> dim[Id::eLast + 1] = { {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {8, 1}, {1, 1}, {8, 8}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {8, 1}, {31, 1}, {1, 1}, {1, 1}, {8, 1}, {1, 1}, {1, 1}, {1, 1}} ;
      return dim[widgetId];
   }

};

struct Button3d
{
   enum Id
   {
      eBtnSil = 0,
      eLast = eBtnSil
   };

   static std::string id2Str(Id widgetId)
   {
        switch(widgetId)
        {
            case eBtnSil: return "BtnSil";
            default: return std::string();
        }
   }

   using WidgetType = fp::Button3d;

   static constexpr Vector2d<uint8_t> getDim(Id widgetId)
   {
      constexpr Vector2d<uint8_t> dim[Id::eLast + 1] = { {8, 8}} ;
      return dim[widgetId];
   }

   static uint32_t getVelocityResolution(Id widgetId)
   {
      const uint32_t res[Id::eLast + 1] = { 128} ;
      return res[widgetId];
   }

   static uint32_t getPressureResolution(Id widgetId)
   {
      const uint32_t res[Id::eLast + 1] = { 0} ;
      return res[widgetId];
   }

};

struct Button
{
   enum Id
   {
      eBtnLayout = 0,
      eBtnSel = 1,
      eBtnSession = 2,
      eBtnQuantize = 3,
      eBtnNote = 4,
      eBtnMute = 5,
      eBtnUser = 6,
      eBtnDoubleLoop = 7,
      eBtnStopClip = 8,
      eBtnLeftArrow = 9,
      eBtnMetronome = 10,
      eBtnSelect = 11,
      eBtnMix = 12,
      eBtnB = 13,
      eBtnDuplicate = 14,
      eBtnPageRight = 15,
      eBtnT = 16,
      eBtnPlay = 17,
      eBtnAccent = 18,
      eBtnShift = 19,
      eBtnSetup = 20,
      eBtnUpArrow = 21,
      eBtnFixedLength = 22,
      eBtnSolo = 23,
      eBtnTapTempo = 24,
      eBtnDevice = 25,
      eBtnScale = 26,
      eBtnAddDevice = 27,
      eBtnAutomate = 28,
      eBtnOctaveDown = 29,
      eBtnUndo = 30,
      eBtnConvert = 31,
      eBtnAddTrack = 32,
      eBtnOctaveUp = 33,
      eBtnRightArrow = 34,
      eBtnDelete = 35,
      eBtnMaster = 36,
      eBtnNew = 37,
      eBtnPageLeft = 38,
      eBtnRecord = 39,
      eBtnRepeat = 40,
      eBtnDownArrow = 41,
      eBtnClip = 42,
      eBtnBrowse = 43,
      eLast = eBtnBrowse
   };

   static std::string id2Str(Id widgetId)
   {
        switch(widgetId)
        {
            case eBtnLayout: return "BtnLayout";
            case eBtnSel: return "BtnSel";
            case eBtnSession: return "BtnSession";
            case eBtnQuantize: return "BtnQuantize";
            case eBtnNote: return "BtnNote";
            case eBtnMute: return "BtnMute";
            case eBtnUser: return "BtnUser";
            case eBtnDoubleLoop: return "BtnDoubleLoop";
            case eBtnStopClip: return "BtnStopClip";
            case eBtnLeftArrow: return "BtnLeftArrow";
            case eBtnMetronome: return "BtnMetronome";
            case eBtnSelect: return "BtnSelect";
            case eBtnMix: return "BtnMix";
            case eBtnB: return "BtnB";
            case eBtnDuplicate: return "BtnDuplicate";
            case eBtnPageRight: return "BtnPageRight";
            case eBtnT: return "BtnT";
            case eBtnPlay: return "BtnPlay";
            case eBtnAccent: return "BtnAccent";
            case eBtnShift: return "BtnShift";
            case eBtnSetup: return "BtnSetup";
            case eBtnUpArrow: return "BtnUpArrow";
            case eBtnFixedLength: return "BtnFixedLength";
            case eBtnSolo: return "BtnSolo";
            case eBtnTapTempo: return "BtnTapTempo";
            case eBtnDevice: return "BtnDevice";
            case eBtnScale: return "BtnScale";
            case eBtnAddDevice: return "BtnAddDevice";
            case eBtnAutomate: return "BtnAutomate";
            case eBtnOctaveDown: return "BtnOctaveDown";
            case eBtnUndo: return "BtnUndo";
            case eBtnConvert: return "BtnConvert";
            case eBtnAddTrack: return "BtnAddTrack";
            case eBtnOctaveUp: return "BtnOctaveUp";
            case eBtnRightArrow: return "BtnRightArrow";
            case eBtnDelete: return "BtnDelete";
            case eBtnMaster: return "BtnMaster";
            case eBtnNew: return "BtnNew";
            case eBtnPageLeft: return "BtnPageLeft";
            case eBtnRecord: return "BtnRecord";
            case eBtnRepeat: return "BtnRepeat";
            case eBtnDownArrow: return "BtnDownArrow";
            case eBtnClip: return "BtnClip";
            case eBtnBrowse: return "BtnBrowse";
            default: return std::string();
        }
   }

   using WidgetType = fp::Button;

   static constexpr Vector2d<uint8_t> getDim(Id widgetId)
   {
      constexpr Vector2d<uint8_t> dim[Id::eLast + 1] = { {1, 1}, {8, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {8, 1}, {1, 1}, {1, 1}, {8, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}} ;
      return dim[widgetId];
   }

};

struct Display
{
   enum Id
   {
      eDisplay = 0,
      eLast = eDisplay
   };

   static std::string id2Str(Id widgetId)
   {
        switch(widgetId)
        {
            case eDisplay: return "Display";
            default: return std::string();
        }
   }

   static constexpr Vector2d<uint8_t> getDim(Id widgetId)
   {
      constexpr Vector2d<uint8_t> dim[Id::eLast + 1] = { {1, 1}} ;
      return dim[widgetId];
   }

   static const gfx::Resolution &getResolution(Id widgetId)
   {
      static const Vector2d<uint32_t> res[Id::eLast + 1] = { { 960, 160 }} ;
      return res[widgetId];
   }
};

struct Encoder
{
   enum Id
   {
      eEncoderMetronome = 0,
      eEncoderMain = 1,
      eEncoderTempo = 2,
      eEncoder = 3,
      eLast = eEncoder
   };

   static std::string id2Str(Id widgetId)
   {
        switch(widgetId)
        {
            case eEncoderMetronome: return "EncoderMetronome";
            case eEncoderMain: return "EncoderMain";
            case eEncoderTempo: return "EncoderTempo";
            case eEncoder: return "Encoder";
            default: return std::string();
        }
   }

   using WidgetType = fp::Encoder;

   static constexpr Vector2d<uint8_t> getDim(Id widgetId)
   {
      constexpr Vector2d<uint8_t> dim[Id::eLast + 1] = { {1, 1}, {1, 1}, {1, 1}, {8, 1}} ;
      return dim[widgetId];
   }

};

struct Positioner
{
   enum Id
   {
      eLast = -1
   };

   static std::string id2Str(Id widgetId)
   {
        switch(widgetId)
        {
            default: return std::string();
        }
   }

   static constexpr Vector2d<uint8_t> getDim(Id widgetId)
   {
      constexpr Vector2d<uint8_t> dim = {0,0};
      return dim;
   }

   static uint32_t getResolution(Id widgetId)
   {
      const uint32_t res = 0;
      return res;
   }
};

struct TouchSurface
{
   enum Id
   {
      eTouchStrip = 0,
      eLast = eTouchStrip
   };

   static std::string id2Str(Id widgetId)
   {
        switch(widgetId)
        {
            case eTouchStrip: return "TouchStrip";
            default: return std::string();
        }
   }

   using WidgetType = fp::TouchSurface;

   static constexpr Vector2d<uint8_t> getDim(Id widgetId)
   {
      constexpr Vector2d<uint8_t> dim[Id::eLast + 1] = { {1, 1}} ;
      return dim[widgetId];
   }

   static const gfx::Resolution &getResolution(Id widgetId)
   {
      static const Vector2d<uint32_t> res[Id::eLast + 1] = { { 16384, 0 }} ;
      return res[widgetId];
   }
};

struct Button5d
{
   enum Id
   {
      eLast = -1
   };

   static std::string id2Str(Id widgetId)
   {
        switch(widgetId)
        {
            default: return std::string();
        }
   }

   using WidgetType = fp::Button5d;

   static constexpr Vector2d<uint8_t> getDim(Id widgetId)
   {
      constexpr Vector2d<uint8_t> dim = {0,0};
      return dim;
   }

   static uint32_t getVelocityResolution(Id widgetId)
   {
      const uint32_t res = 0;
      return res;
   }

   static uint32_t getPressureResolution(Id widgetId)
   {
      const uint32_t res = 0;
      return res;
   }

   static const Vector2d<uint32_t> &getSurfaceResolution(Id widgetId)
   {
      static const Vector2d<uint32_t> res = {0,0};
      return res;
   }
};

}; // struct Push2Topology
} // namespace fp
#endif