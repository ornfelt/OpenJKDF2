/*
 *  Copyright (c) 2010 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef MEDIA_BASE_VIDEO_ADAPTER_H_
#define MEDIA_BASE_VIDEO_ADAPTER_H_

#include <stdint.h>

#include <utility>

#include "absl/types/optional.h"
#include "api/video/video_source_interface.h"
#include "media/base/video_common.h"
#include "rtc_base/constructor_magic.h"
#include "rtc_base/critical_section.h"
#include "rtc_base/thread_annotations.h"

namespace cricket {

// VideoAdapter adapts an input video frame to an output frame based on the
// specified input and output formats. The adaptation includes dropping frames
// to reduce frame rate and scaling frames.
// VideoAdapter is thread safe.
class VideoAdapter {
 public:
  VideoAdapter();
  // The source requests output frames whose width and height are divisible
  // by |source_resolution_alignment|.
  explicit VideoAdapter(int source_resolution_alignment);
  virtual ~VideoAdapter();

  // Return the adapted resolution and cropping parameters given the
  // input resolution. The input frame should first be cropped, then
  // scaled to the final output resolution. Returns true if the frame
  // should be adapted, and false if it should be dropped.
  bool AdaptFrameResolution(int in_width,
                            int in_height,
                            int64_t in_timestamp_ns,
                            int* cropped_width,
                            int* cropped_height,
                            int* out_width,
                            int* out_height)
      RTC_LOCKS_EXCLUDED(critical_section_);

  // DEPRECATED. Please use OnOutputFormatRequest below.
  // TODO(asapersson): Remove this once it is no longer used.
  // Requests the output frame size and frame interval from
  // |AdaptFrameResolution| to not be larger than |format|. Also, the input
  // frame size will be cropped to match the requested aspect ratio. The
  // requested aspect ratio is orientation agnostic and will be adjusted to
  // maintain the input orientation, so it doesn't matter if e.g. 1280x720 or
  // 720x1280 is requested.
  // Note: Should be called from the source only.
  void OnOutputFormatRequest(const absl::optional<VideoFormat>& format)
      RTC_LOCKS_EXCLUDED(critical_section_);

  // Requests output frame size and frame interval from |AdaptFrameResolution|.
  // |target_aspect_ratio|: The input frame size will be cropped to match the
  // requested aspect ratio. The aspect ratio is orientation agnostic and will
  // be adjusted to maintain the input orientation (i.e. it doesn't matter if
  // e.g. <1280,720> or <720,1280> is requested).
  // |max_pixel_count|: The maximum output frame size.
  // |max_fps|: The maximum output framerate.
  // Note: Should be called from the source only.
  void OnOutputFormatRequest(
      const absl::optional<std::pair<int, int>>& target_aspect_ratio,
      const absl::optional<int>& max_pixel_count,
      const absl::optional<int>& max_fps) RTC_LOCKS_EXCLUDED(critical_section_);

  // Same as above, but allows setting two different target aspect ratios
  // depending on incoming frame orientation. This gives more fine-grained
  // control and can e.g. be used to force landscape video to be cropped to
  // portrait video.
  void OnOutputFormatRequest(
      const absl::optional<std::pair<int, int>>& target_landscape_aspect_ratio,
      const absl::optional<int>& max_landscape_pixel_count,
      const absl::optional<std::pair<int, int>>& target_portrait_aspect_ratio,
      const absl::optional<int>& max_portrait_pixel_count,
      const absl::optional<int>& max_fps) RTC_LOCKS_EXCLUDED(critical_section_);

  // Requests the output frame size from |AdaptFrameResolution| to have as close
  // as possible to |sink_wants.target_pixel_count| pixels (if set)
  // but no more than |sink_wants.max_pixel_count|.
  // |sink_wants.max_framerate_fps| is essentially analogous to
  // |sink_wants.max_pixel_count|, but for framerate rather than resolution.
  // Set |sink_wants.max_pixel_count| and/or |sink_wants.max_framerate_fps| to
  // std::numeric_limit<int>::max() if no upper limit is desired.
  // The sink resolution alignment requirement is given by
  // |sink_wants.resolution_alignment|.
  // Note: Should be called from the sink only.
  void OnSinkWants(const rtc::VideoSinkWants& sink_wants)
      RTC_LOCKS_EXCLUDED(critical_section_);

 private:
  // Determine if frame should be dropped based on input fps and requested fps.
  bool KeepFrame(int64_t in_timestamp_ns)
      RTC_EXCLUSIVE_LOCKS_REQUIRED(critical_section_);

  int frames_in_ RTC_GUARDED_BY(critical_section_);  // Number of input frames.
  int frames_out_
      RTC_GUARDED_BY(critical_section_);  // Number of output frames.
  int frames_scaled_
      RTC_GUARDED_BY(critical_section_);  // Number of frames scaled.
  int adaption_changes_
      RTC_GUARDED_BY(critical_section_);  // Number of changes in scale factor.
  int previous_width_
      RTC_GUARDED_BY(critical_section_);  // Previous adapter output width.
  int previous_height_
      RTC_GUARDED_BY(critical_section_);  // Previous adapter output height.
  const bool variable_start_scale_factor_;

  // The fixed source resolution alignment requirement.
  const int source_resolution_alignment_;
  // The currently applied resolution alignment, as given by the requirements:
  //  - the fixed |source_resolution_alignment_|; and
  //  - the latest |sink_wants.resolution_alignment|.
  int resolution_alignment_ RTC_GUARDED_BY(critical_section_);

  // The target timestamp for the next frame based on requested format.
  absl::optional<int64_t> next_frame_timestamp_ns_
      RTC_GUARDED_BY(critical_section_);

  // Max number of pixels/fps requested via calls to OnOutputFormatRequest,
  // OnResolutionFramerateRequest respectively.
  // The adapted output format is the minimum of these.
  absl::optional<std::pair<int, int>> target_landscape_aspect_ratio_
      RTC_GUARDED_BY(critical_section_);
  absl::optional<int> max_landscape_pixel_count_
      RTC_GUARDED_BY(critical_section_);
  absl::optional<std::pair<int, int>> target_portrait_aspect_ratio_
      RTC_GUARDED_BY(critical_section_);
  absl::optional<int> max_portrait_pixel_count_
      RTC_GUARDED_BY(critical_section_);
  absl::optional<int> max_fps_ RTC_GUARDED_BY(critical_section_);
  int resolution_request_target_pixel_count_ RTC_GUARDED_BY(critical_section_);
  int resolution_request_max_pixel_count_ RTC_GUARDED_BY(critical_section_);
  int max_framerate_request_ RTC_GUARDED_BY(critical_section_);

  // The critical section to protect the above variables.
  rtc::CriticalSection critical_section_;

  RTC_DISALLOW_COPY_AND_ASSIGN(VideoAdapter);
};

}  // namespace cricket

#endif  // MEDIA_BASE_VIDEO_ADAPTER_H_
