#include "SharedAdaptiveCard.h"
#include "ParseUtil.h"

#include "Container.h"
#include "ShowCardAction.h"
#include "TextBlock.h"

using namespace AdaptiveCards;

AdaptiveCard::AdaptiveCard()
{
}

AdaptiveCard::AdaptiveCard(std::string version,
    std::string minVersion,
    std::string fallbackText,
    std::string backgroundImage,
    ContainerStyle style,
    std::string speak,
<<<<<<< HEAD
    std::locale language) :
=======
    std::string language) :
>>>>>>> 2e3dbcfc7468b987d0b9cf2a4bdb92d72a2c47a0
    m_version(version),
    m_minVersion(minVersion),
    m_fallbackText(fallbackText),
    m_backgroundImage(backgroundImage),
    m_style(style),
    m_speak(speak),
    m_language(language)
{
}

AdaptiveCard::AdaptiveCard(std::string version,
    std::string minVersion,
    std::string fallbackText,
    std::string backgroundImage,
    ContainerStyle style,
    std::string speak,
<<<<<<< HEAD
    std::locale language,
=======
    std::string language,
>>>>>>> 2e3dbcfc7468b987d0b9cf2a4bdb92d72a2c47a0
    std::vector<std::shared_ptr<BaseCardElement>>& body, std::vector<std::shared_ptr<BaseActionElement>>& actions) :
    m_version(version),
    m_minVersion(minVersion),
    m_fallbackText(fallbackText),
    m_backgroundImage(backgroundImage),
    m_style(style),
    m_speak(speak),
    m_language(language),
    m_body(body),
    m_actions(actions)
{
}

#ifdef __ANDROID__
std::shared_ptr<AdaptiveCard> AdaptiveCard::DeserializeFromFile(
    const std::string& jsonFile,
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration) throw(AdaptiveCards::AdaptiveCardParseException)
#else
std::shared_ptr<AdaptiveCard> AdaptiveCard::DeserializeFromFile(
    const std::string& jsonFile,
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration)
#endif // __ANDROID__
{
    std::ifstream jsonFileStream(jsonFile);

    Json::Value root;
    jsonFileStream >> root;

    return AdaptiveCard::Deserialize(root, elementParserRegistration, actionParserRegistration);
}

#ifdef __ANDROID__
std::shared_ptr<AdaptiveCard> AdaptiveCard::Deserialize(
    const Json::Value& json,
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration) throw(AdaptiveCards::AdaptiveCardParseException)
#else
std::shared_ptr<AdaptiveCard> AdaptiveCard::Deserialize(
    const Json::Value& json,
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration)
#endif // __ANDROID__
{
    ParseUtil::ThrowIfNotJsonObject(json);

    // Verify this is an adaptive card
    ParseUtil::ExpectTypeString(json, CardElementType::AdaptiveCard);

    std::string version = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Version);
    std::string minVersion = ParseUtil::GetString(json, AdaptiveCardSchemaKey::MinVersion);
    std::string fallbackText = ParseUtil::GetString(json, AdaptiveCardSchemaKey::FallbackText);
    std::string backgroundImageUrl = ParseUtil::GetString(json, AdaptiveCardSchemaKey::BackgroundImageUrl);
    std::string backgroundImage = backgroundImageUrl != "" ? backgroundImageUrl :
        ParseUtil::GetString(json, AdaptiveCardSchemaKey::BackgroundImage);
    std::string speak = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Speak);
    ContainerStyle style = ParseUtil::GetEnumValue<ContainerStyle>(json, AdaptiveCardSchemaKey::Style, ContainerStyle::None, ContainerStyleFromString);
<<<<<<< HEAD
    std::string language = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Language);
=======
    std::string language = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Language, true /* isRequired */);
>>>>>>> 2e3dbcfc7468b987d0b9cf2a4bdb92d72a2c47a0
    
    std::locale locale;
    try
    {
        locale = std::locale(language);
    }
    catch (std::runtime_error error)
    {
<<<<<<< HEAD
        // throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Language " + language + " is not recognized.");
        // generate warning for language created incorrectly
=======
        throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Language " + language + " is not recognized.");
>>>>>>> 2e3dbcfc7468b987d0b9cf2a4bdb92d72a2c47a0
    }

    if (elementParserRegistration == nullptr)
    {
        elementParserRegistration.reset(new ElementParserRegistration());
    }
    if (actionParserRegistration == nullptr)
    {
        actionParserRegistration.reset(new ActionParserRegistration());
    }

    // Parse body
    auto body = ParseUtil::GetElementCollection(elementParserRegistration, actionParserRegistration, json, AdaptiveCardSchemaKey::Body, false, locale);

    // Parse actions if present
    auto actions = ParseUtil::GetActionCollection(elementParserRegistration, actionParserRegistration, json, AdaptiveCardSchemaKey::Actions, false, locale);

<<<<<<< HEAD
    auto result = std::make_shared<AdaptiveCard>(version, minVersion, fallbackText, backgroundImage, style, speak, locale, body, actions);
=======
    auto result = std::make_shared<AdaptiveCard>(version, minVersion, fallbackText, backgroundImage, style, speak, language, body, actions);
>>>>>>> 2e3dbcfc7468b987d0b9cf2a4bdb92d72a2c47a0
    return result;
}

#ifdef __ANDROID__
std::shared_ptr<AdaptiveCard> AdaptiveCard::DeserializeFromString(
    const std::string& jsonString,
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration) throw(AdaptiveCards::AdaptiveCardParseException)
#else
std::shared_ptr<AdaptiveCard> AdaptiveCard::DeserializeFromString(
    const std::string& jsonString,
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration)
#endif // __ANDROID__
{
    return AdaptiveCard::Deserialize(ParseUtil::GetJsonValueFromString(jsonString), elementParserRegistration, actionParserRegistration);
}

Json::Value AdaptiveCard::SerializeToJsonValue()
{
    Json::Value root;
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = CardElementTypeToString(CardElementType::AdaptiveCard);
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Version)] = GetVersion();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MinVersion)] = GetMinVersion();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FallbackText)] = GetFallbackText();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::BackgroundImage)] = GetBackgroundImage();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Speak)] = GetSpeak();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Language)] = GetLanguage();

    ContainerStyle style = GetStyle();
    if (style != ContainerStyle::None)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ContainerStyleToString(GetStyle());
    }

    std::string bodyPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Body);
    root[bodyPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : GetBody())
    {
        root[bodyPropertyName].append(cardElement->SerializeToJsonValue());
    }

    std::string actionsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Actions);
    root[actionsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& action : GetActions())
    {
        root[actionsPropertyName].append(action->SerializeToJsonValue());
    }

    return root;
}

std::string AdaptiveCard::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

std::string AdaptiveCard::GetVersion() const
{
    return m_version;
}

void AdaptiveCard::SetVersion(const std::string value)
{
    m_version = value;
}

std::string AdaptiveCard::GetMinVersion() const
{
    return m_minVersion;
}

void AdaptiveCard::SetMinVersion(const std::string value)
{
    m_minVersion = value;
}

std::string AdaptiveCard::GetFallbackText() const
{
    return m_fallbackText;
}

void AdaptiveCard::SetFallbackText(const std::string value)
{
    m_fallbackText = value;
}

std::string AdaptiveCard::GetBackgroundImage() const
{
    return m_backgroundImage;
}

void AdaptiveCard::SetBackgroundImage(const std::string value)
{
    m_backgroundImage = value;
}

std::string AdaptiveCard::GetSpeak() const
{
    return m_speak;
}

void AdaptiveCard::SetSpeak(const std::string value)
{
    m_speak = value;
}

ContainerStyle AdaptiveCards::AdaptiveCard::GetStyle() const
{
    return m_style;
}

void AdaptiveCards::AdaptiveCard::SetStyle(const ContainerStyle value)
{
    m_style = value;
}

std::string AdaptiveCard::GetLanguage() const
{
    return m_language.name();
}

void AdaptiveCard::SetLanguage(const std::locale value)
{
    m_language = value;
    // Propagate language to TextBlocks, Containers and showCardActions
    for (auto& bodyElement : m_body)
    {
        if (bodyElement->GetElementType() == CardElementType::Container)
        {
            auto container = std::dynamic_pointer_cast<Container>(bodyElement);
            if (container != nullptr)
            {
                container->SetLanguage(value);
            }
        }
        else
        {
            if (bodyElement->GetElementType() == CardElementType::TextBlock)
            {
                auto textBlock = std::dynamic_pointer_cast<TextBlock>(bodyElement);
                if (textBlock != nullptr)
                {
                    textBlock->SetLanguage(value);
                }
            }
        }
    }

    for (auto& actionElement : m_actions)
    {
        if (actionElement->GetElementType() == ActionType::ShowCard)
        {
            auto showCard = std::dynamic_pointer_cast<ShowCardAction>(actionElement);
            if (showCard != nullptr)
            {
                showCard->SetLanguage(value);
            }
        }
    }
    return m_language;
}

const CardElementType AdaptiveCard::GetElementType() const
{
    return CardElementType::AdaptiveCard;
}

std::vector<std::shared_ptr<BaseCardElement>>& AdaptiveCard::GetBody()
{
    return m_body;
}

std::vector<std::shared_ptr<BaseActionElement>>& AdaptiveCard::GetActions()
{
    return m_actions;
}
