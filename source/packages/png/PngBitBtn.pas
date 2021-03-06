unit PngBitBtn;

interface

uses
  Windows, Messages, Classes, Graphics, Controls, Buttons, pngimage, PngFunctions;

type
  TPngBitBtn = class(TBitBtn)
  private
    FPngImage: TPngImage;
    FPngOptions: TPngOptions;
    FCanvas: TCanvas;
    FLastKind: TBitBtnKind;
    FImageFromAction: Boolean;
    FMouseInControl: Boolean;
    IsFocused: Boolean;
    function PngImageStored: Boolean;
    procedure SetPngImage(const Value: TPngImage);
    procedure SetPngOptions(const Value: TPngOptions);
    procedure CNDrawItem(var Message: TWMDrawItem); message CN_DRAWITEM;
    procedure CMMouseEnter(var Message: TMessage); message CM_MOUSEENTER;
    procedure CMMouseLeave(var Message: TMessage); message CM_MOUSELEAVE;
  protected
    procedure ActionChange(Sender: TObject; CheckDefaults: Boolean); override;
    procedure SetButtonStyle(ADefault: Boolean); override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    property PngImage: TPngImage read FPngImage write SetPngImage stored PngImageStored;
    property PngOptions: TPngOptions read FPngOptions write SetPngOptions default [pngBlendOnDisabled];
    property Glyph stored False;
    property NumGlyphs stored False;
  end;

implementation

uses
  ActnList, Themes, PngButtonFunctions;

{$IF RTLVersion < 23.0 }
type
  TThemeServicesHelper = class helper for TThemeServices
  private
    function GetEnabled: Boolean;
  public
    function GetElementContentRect(DC: HDC; Details: TThemedElementDetails; const BoundingRect: TRect;
        out ContentRect: TRect): Boolean; overload;
    property Enabled: Boolean read GetEnabled;
  end;

function TThemeServicesHelper.GetElementContentRect(DC: HDC; Details: TThemedElementDetails; const BoundingRect: TRect;
    out ContentRect: TRect): Boolean;
begin
  ContentRect := Self.ContentRect(DC, Details, BoundingRect);
  Result := true;
end;

function TThemeServicesHelper.GetEnabled: Boolean;
begin
  Result := ThemesEnabled;
end;

function StyleServices: TThemeServices;
begin
  result := ThemeServices;
end;
{$IFEND}

{ TPngBitBtn }

constructor TPngBitBtn.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FPngImage := TPngImage.Create;
  FPngOptions := [pngBlendOnDisabled];
  FCanvas := TCanvas.Create;
  FLastKind := bkCustom;
  FImageFromAction := False;
end;

destructor TPngBitBtn.Destroy;
begin
  FPngImage.Free;
  FCanvas.Free;
  inherited Destroy;
end;

procedure TPngBitBtn.ActionChange(Sender: TObject; CheckDefaults: Boolean);
begin
  inherited ActionChange(Sender, CheckDefaults);
  if Sender is TCustomAction then begin
    with TCustomAction(Sender) do begin
      //Copy image from action's imagelist
      if (PngImage.Empty or FImageFromAction) and (ActionList <> nil) and
        (ActionList.Images <> nil) and (ImageIndex >= 0) and (ImageIndex <
        ActionList.Images.Count) then begin
        CopyImageFromImageList(FPngImage, ActionList.Images, ImageIndex);
        FImageFromAction := True;
      end;
    end;
  end;
end;

procedure TPngBitBtn.SetButtonStyle(ADefault: Boolean);
begin
  inherited SetButtonStyle(ADefault);
  if ADefault <> IsFocused then begin
    IsFocused := ADefault;
    Refresh;
  end;
end;

function TPngBitBtn.PngImageStored: Boolean;
begin
  Result := not FImageFromAction;
end;

procedure TPngBitBtn.SetPngImage(const Value: TPngImage);
begin
  //This is all neccesary, because you can't assign a nil to a TPngImage
  if Value = nil then begin
    FPngImage.Free;
    FPngImage := TPngImage.Create;
  end
  else begin
    FPngImage.Assign(Value);
  end;

  //To work around the gamma-problem
  with FPngImage do
    if not Empty and (Header.ColorType in [COLOR_RGB, COLOR_RGBALPHA, COLOR_PALETTE]) then
      Chunks.RemoveChunk(Chunks.ItemFromClass(TChunkgAMA));

  FImageFromAction := False;
  Repaint;
end;

procedure TPngBitBtn.SetPngOptions(const Value: TPngOptions);
begin
  if FPngOptions <> Value then begin
    FPngOptions := Value;
    Repaint;
  end;
end;

procedure TPngBitBtn.CNDrawItem(var Message: TWMDrawItem);
var
  R, PaintRect: TRect;
  GlyphPos, TextPos: TPoint;
  IsDown, IsDefault: Boolean;
  Flags: Cardinal;
  Button: TThemedButton;
  Details: TThemedElementDetails;
begin
  R := ClientRect;
  FCanvas.Handle := Message.DrawItemStruct^.hDC;
  FCanvas.Font := Self.Font;
  IsDown := Message.DrawItemStruct^.itemState and ODS_SELECTED <> 0;
  IsDefault := Message.DrawItemStruct^.itemState and ODS_FOCUS <> 0;

  //Draw the border
  if StyleServices.Enabled then begin
    //Themed border
    if not Enabled then
      Button := tbPushButtonDisabled
    else if IsDown then
      Button := tbPushButtonPressed
    else if FMouseInControl then
      Button := tbPushButtonHot
    else if IsFocused or IsDefault then
      Button := tbPushButtonDefaulted
    else
      Button := tbPushButtonNormal;

    //Paint the background, border, and finally get the inner rect
    Details := StyleServices.GetElementDetails(Button);
    StyleServices.DrawParentBackground(Handle, Message.DrawItemStruct.hDC, @Details, True);
    StyleServices.DrawElement(Message.DrawItemStruct.hDC, Details, Message.DrawItemStruct.rcItem);
    StyleServices.GetElementContentRect(FCanvas.Handle, Details, Message.DrawItemStruct.rcItem, R);
  end
  else begin
    //Draw the outer border, when focused
    if IsFocused or IsDefault then begin
      FCanvas.Pen.Color := clWindowFrame;
      FCanvas.Pen.Width := 1;
      FCanvas.Brush.Style := bsClear;
      FCanvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
      InflateRect(R, -1, -1);
    end;
    //Draw the inner border
    if IsDown then begin
      FCanvas.Pen.Color := clBtnShadow;
      FCanvas.Pen.Width := 1;
      FCanvas.Brush.Color := clBtnFace;
      FCanvas.Rectangle(R.Left, R.Top, R.Right, R.Bottom);
      InflateRect(R, -1, -1);
    end
    else begin
      Flags := DFCS_BUTTONPUSH or DFCS_ADJUSTRECT;
      if Message.DrawItemStruct.itemState and ODS_DISABLED <> 0 then
        Flags := Flags or DFCS_INACTIVE;
      DrawFrameControl(Message.DrawItemStruct.hDC, R, DFC_BUTTON, Flags);
    end;
    //Adjust the rect when focused and/or down
    if IsFocused then begin
      R := ClientRect;
      InflateRect(R, -1, -1);
    end;
    if IsDown then
      OffsetRect(R, 1, 1);
  end;

  //Calculate the position of the PNG glyph
  CalcButtonLayout(FCanvas, FPngImage, ClientRect, IsDown, False, Caption,
    Layout, Margin, Spacing, GlyphPos, TextPos, DrawTextBiDiModeFlags(0));

  //Draw the image
  if (FPngImage <> nil) and (Kind = bkCustom) and not FPngImage.Empty then begin
    PaintRect := Bounds(GlyphPos.X, GlyphPos.Y, FPngImage.Width, FPngImage.Height);
    if Enabled then
      DrawPNG(FPngImage, FCanvas, PaintRect, [])
    else
      DrawPNG(FPngImage, FCanvas, PaintRect, FPngOptions);
  end;

  //Draw the text
  if Length(Caption) > 0 then begin
    PaintRect := Rect(TextPos.X, TextPos.Y, Width, Height);
    FCanvas.Brush.Style := bsClear;
    //grayed Caption when disabled
    if not Enabled then begin
      OffsetRect(PaintRect, 1, 1);
      FCanvas.Font.Color := clBtnHighlight;
      DrawText(FCanvas.Handle, PChar(Caption), -1, PaintRect,
        DrawTextBiDiModeFlags(0) or DT_TOP or DT_LEFT or DT_SINGLELINE);
      OffsetRect(PaintRect, -1, -1);
      FCanvas.Font.Color := clBtnShadow;
    end;

    DrawText(FCanvas.Handle, PChar(Caption), -1, PaintRect,
      DrawTextBiDiModeFlags(0) or DT_TOP or DT_LEFT or DT_SINGLELINE);
  end;

  //Draw the focus rectangle
  if IsFocused and IsDefault then begin
    if not StyleServices.Enabled then begin
      R := ClientRect;
      InflateRect(R, -3, -3);
    end;
    FCanvas.Pen.Color := clWindowFrame;
    FCanvas.Brush.Color := clBtnFace;
    DrawFocusRect(FCanvas.Handle, R);
  end;

  FLastKind := Kind;
  FCanvas.Handle := 0;
end;

procedure TPngBitBtn.CMMouseEnter(var Message: TMessage);
begin
  inherited;
  if StyleServices.Enabled and not FMouseInControl and not (csDesigning in ComponentState) then begin
    FMouseInControl := True;
    Repaint;
  end;
end;

procedure TPngBitBtn.CMMouseLeave(var Message: TMessage);
begin
  inherited;
  if StyleServices.Enabled and FMouseInControl then begin
    FMouseInControl := False;
    Repaint;
  end;
end;

end.
